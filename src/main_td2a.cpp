/**
 * @file main_td1c.cpp
 * @brief Main file for tutorial question 1c
 */

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
		std::cerr << "Usage: " << argv[0] << " <nLoops> <nTasks>\n";
		return 1;
	}
	unsigned int nLoops = std::stoul(argv[1]);
	unsigned int nTasks = std::stoul(argv[2]);

	// Thread
	ThreadData data{nLoops, 0};
	std::vector<pthread_t> incrementThreads(nTasks);

	// Time
	timespec start_ts, end_ts{};
	clock_gettime(CLOCK_REALTIME, &start_ts);
	for (auto &thread : incrementThreads) {
		pthread_create(&thread, nullptr, call_incr, &data);
	}
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
