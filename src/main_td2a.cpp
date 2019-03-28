/**
 * @file main_td2a.cpp
 * @brief Main file for tutorial question 2a
 */

#include "timespec.h"

#include <ctime>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>

/**
 * @brief A structure to share data between threads
 */
struct ThreadData
{
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
void incr(unsigned int nLoops, volatile double *pCounter)
{
		for (unsigned int i(0); i < nLoops; ++i) { (*pCounter) += 1.0; }
}

/**
 * @brief A wrapper to call `incr` in a pthread
 *
 * @param[in,out] v_data a pointer to the data passed to the thread
 */
void *call_incr(void *v_data)
{
		ThreadData *p_data = reinterpret_cast<ThreadData *>(v_data);
		incr(p_data->nLoops, &p_data->counter);
		return v_data;
}

int main(int argc, char **argv)
{
		if (argc < 3)
		{
				std::cerr << "Usage: " << argv[0] << " <nLoops> <nTasks>\n";
				return 1;
		}

		unsigned int nLoops = std::stoul(argv[1]);
		unsigned int nTasks = std::stoul(argv[2]);

		// Thread
		ThreadData			   data{nLoops, 0};
		std::vector<pthread_t> incrementThreads(nTasks);

		// Time
		timespec start_ts, end_ts{};

		clock_gettime(CLOCK_REALTIME, &start_ts);

		for (auto &thread : incrementThreads)
		{ pthread_create(&thread, nullptr, call_incr, &data); }

		for (auto &thread : incrementThreads)
		{ pthread_join(thread, nullptr); }

		clock_gettime(CLOCK_REALTIME, &end_ts);

		std::cout << "Execution time: "
				  << timespec_to_ms(end_ts - start_ts) / 1000 << "s"
				  << std::endl;

		std::cout << "Counter: " << data.counter << std::endl;

		// Return
		return 0;
}
