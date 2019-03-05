/**
 * @file main_td2b.cpp
 * @brief Main file for tutorial question 2b
 */

#include <cstring>
#include <ctime>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>

#include "timespec.h"

/**
 * @brief A structure to share data between threads
 */
struct ThreadData {
	/// The number of loops to perform
	volatile unsigned int nLoops;
	/// The counter to increment
	volatile double counter;
};

/**
 * @brief A function to increment a counter
 *
 * @param nLoops the number of loops to perform
 * @param[in,out] pCounter a pointer to the counter to increment
 */
void incr(unsigned int nLoops, volatile double *pCounter) {
	for (unsigned int i(0); i < nLoops; ++i) {
		(*pCounter) += 1.0;
	}
	return;
}

/**
 * @brief A wrapper to call `incr` in a pthread
 *
 * @param v_data[in,out] a pointer to the data passed to the thread
 */
void *call_incr(void *v_data) {
	ThreadData *p_data = reinterpret_cast<ThreadData *>(v_data);
	incr(p_data->nLoops, &p_data->counter);
	return v_data;
}

int main(int argc, char **argv) {
	if (argc < 3) {
		std::cerr << "Usage: " << argv[0] << " <nLoops> <nTasks> [schedPolicy]\n";
		return 1;
	}
	unsigned int nLoops = std::stoul(argv[1]);
	unsigned int nTasks = std::stoul(argv[2]);
	int schedPolicy(SCHED_OTHER);
	if (argc == 4) {
		if (!strcmp(argv[3], "SCHED_RR")) {
			schedPolicy = SCHED_RR;
		} else if (!strcmp(argv[3], "SCHED_FIFO")) {
			schedPolicy = SCHED_FIFO;
		}
	}

	// Configure main thread
	sched_param schedParam;
	schedParam.sched_priority = sched_get_priority_max(schedPolicy);
	pthread_setschedparam(pthread_self(), schedPolicy, &schedParam);

	// Thread
	ThreadData data{nLoops, 0};
	std::vector<pthread_t> incrementThreads(nTasks);
	// Thread attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	sched_param schedParams;
	if (schedPolicy == SCHED_OTHER) {
		schedParams.sched_priority = 0;
	} else {
		schedParams.sched_priority = 9;
	}
	pthread_attr_setschedpolicy(&attr, schedPolicy);
	pthread_attr_setschedparam(&attr, &schedParams);

	// Time
	timespec start_ts, end_ts{};
	clock_gettime(CLOCK_REALTIME, &start_ts);
	// Create threads
	for (auto &thread : incrementThreads) {
		pthread_create(&thread, &attr, call_incr, &data);
	}
	// Destroy thread attributes
	pthread_attr_destroy(&attr);
	// Join thread
	for (auto &thread : incrementThreads) {
		pthread_join(thread, nullptr);
	}
	clock_gettime(CLOCK_REALTIME, &end_ts);
	std::cout << "Execution time: " << timespec_to_ms(end_ts - start_ts) / 1000
						<< "s\n";
	std::cout << "Counter: " << data.counter << '\n';

	// Return
	return 0;
}
