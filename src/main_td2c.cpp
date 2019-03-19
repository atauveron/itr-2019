/**
 * @file main_td2c.cpp
 * @brief Main file for tutorial question 2c
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
	/// Boolean to indicate whether to use the mutex
	bool useMutex;
	/// Mutex on the counter
	pthread_mutex_t mutex;
};

/**
 * @brief A function to increment a counter
 *
 * @param nLoops the number of loops to perform
 * @param[in,out] pCounter a pointer to the counter to increment
 * @param useMutex a boolean to indicate whether to use a mutex
 * @param pMutex a pointer to the mutex to use
 */
void incr(unsigned int nLoops, volatile double *pCounter, bool useMutex = false,
					pthread_mutex_t *pMutex = nullptr) {
	for (unsigned int i(0); i < nLoops; ++i) {
		if (useMutex) {
			pthread_mutex_lock(pMutex);
		}
		(*pCounter) += 1.0;
		if (useMutex) {
			pthread_mutex_unlock(pMutex);
		}
	}
	return;
}

/**
 * @brief A wrapper to call `incr` in a pthread
 *
 * @param[in,out] v_data a pointer to the data passed to the thread
 */
void *call_incr(void *v_data) {
	ThreadData *p_data = reinterpret_cast<ThreadData *>(v_data);
	incr(p_data->nLoops, &p_data->counter, p_data->useMutex, &p_data->mutex);
	return v_data;
}

int main(int argc, char **argv) {
	if (argc < 3) {
		std::cerr << "Usage: " << argv[0] << " <nLoops> <nTasks> [protected]\n";
		return 1;
	}
	unsigned int nLoops = std::stoul(argv[1]);
	unsigned int nTasks = std::stoul(argv[2]);
	// Set useMutex to true if the third argument is "protected", and to false
	// otherwise.
	bool useMutex(argc == 4 && !strcmp(argv[3], "protected"));

	// Thread
	ThreadData data{nLoops, 0, useMutex, 0};
	pthread_mutex_init(&data.mutex, nullptr);
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
	pthread_mutex_destroy(&data.mutex);
	clock_gettime(CLOCK_REALTIME, &end_ts);
	std::cout << "Execution time: " << timespec_to_ms(end_ts - start_ts) / 1000
						<< "s\n";
	std::cout << "Counter: " << data.counter << '\n';

	// Return
	return 0;
}
