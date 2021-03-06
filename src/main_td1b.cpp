/**
 * @file main_td1b.cpp
 * @brief Main file for tutorial question 1b
 */
#include "timespec.h"

#include <ctime>
#include <iostream>
#include <string>

/**
 * @brief A function to increment a counter
 *
 * @param nLoops the number of loops to perform
 * @param[in,out] pCounter a pointer to the counter to increment
 */
void incr(unsigned int nLoops, double *pCounter)
{
		for (unsigned int i(0); i < nLoops; ++i) { (*pCounter) += 1.0; }
		return;
}

int main(int argc, char **argv)
{
		if (argc < 2)
		{
				std::cerr << "Usage: " << argv[0] << " <nLoops>\n";
				return 1;
		}

		unsigned int nLoops = std::stoul(argv[1]);
		double		 counter(0);
		timespec	 start_ts, end_ts{};

		// Start counter sequence
		clock_gettime(CLOCK_REALTIME, &start_ts);
		incr(nLoops, &counter);
		clock_gettime(CLOCK_REALTIME, &end_ts);

		// Display result
		std::cout << "Execution time: "
				  << timespec_to_ms(end_ts - start_ts) / 1000 << std::endl;

		// Return
		return 0;
}
