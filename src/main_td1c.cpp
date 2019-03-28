/**
 * @file main_td1c.cpp
 * @brief Main file for tutorial question 1c
 */
#include "timespec.h"

#include <climits>
#include <csignal>
#include <ctime>
#include <iostream>
#include <string>

/**
 * @brief A structure to wrap the data sent to the timer
 */
struct StopData
{
		// A boolean indicating whether incrementation of the counter should
		// stop
		volatile bool stop;
};

/**
 * @brief A handler function for the timer
 * This function sets the boolean in structure of type StopData (passed via @p
 * si) to false.
 *
 * @param sig
 * @param si
 */
void handler(int, siginfo_t *si, void *)
{
		StopData *stop = reinterpret_cast<StopData *>(si->si_value.sival_ptr);
		stop->stop	 = true;

		return;
}

/**
 * @brief A function that increments a counter
 *
 * @param nLoops the maximum number of loops to perform
 * @param[in,out] pCounter a pointer to the counter to increment
 * @param[in] pStop a boolean to stop the function early
 * @return the number of loops performed
 */
unsigned incr(unsigned int nLoops, double *pCounter, volatile bool *pStop)
{
		unsigned int i;

		for (i = 0; i < nLoops; ++i)
		{
				if (*pStop) { break; }
				(*pCounter) += 1.0;
		}

		return i;
}

/**
 * @brief A wrapper function to run `incr` for a specified duration
 *
 * @param delay_s the duration for which to run `incr` (in seconds)
 * @return the number of loops performed by `incr`
 */
unsigned int run(long int delay_s)
{
		unsigned int nLoops(UINT_MAX);
		double		 counter(0);
		StopData	 stop{false};

		// Timer
		struct sigaction sa;
		sa.sa_flags		= SA_SIGINFO;
		sa.sa_sigaction = handler;

		sigemptyset(&sa.sa_mask);
		sigaction(SIGRTMIN, &sa, nullptr);

		struct sigevent sev;
		sev.sigev_notify		  = SIGEV_SIGNAL;
		sev.sigev_signo			  = SIGRTMIN;
		sev.sigev_value.sival_ptr = &stop;

		timer_t	tid;
		itimerspec its;
		its.it_value	= {delay_s, 0};
		its.it_interval = {0, 0};

		timer_create(CLOCK_REALTIME, &sev, &tid);
		timer_settime(tid, 0, &its, nullptr);

		// Increment
		timespec start_ts, end_ts{};
		clock_gettime(CLOCK_REALTIME, &start_ts);
		nLoops = incr(nLoops, &counter, &stop.stop);
		clock_gettime(CLOCK_REALTIME, &end_ts);

		// DEBUG
		std::cout << "Execution time: " << timespec_to_ms(end_ts - start_ts)
				  << "ms (requested " << delay_s << "s)" << std::endl;
		std::cout << "Number of loops: " << nLoops << std::endl;

		// Delete timer
		timer_delete(tid);

		// Return
		return nLoops;
}

/**
 * @brief A function that run 2 iterations of `run` for 4 and 6 seconds
 * to find the linear coefficient
 *
 * @param params The coefficients `a` & `b` for the linear relation
 */
void calib(long int *params)
{

		// Run for 4 then 6 seconds
		unsigned int nLoops4 = run(4);
		unsigned int nLoops6 = run(6);

		// Compute parameters
		long int slope  = (nLoops6 - nLoops4) / 2;
		long int offset = (long int)nLoops4 - 4 * slope;

		params[0] = slope;
		params[1] = offset;

		// Return
		return;
}

int main()
{
		long int calib_params[2];

		// Start calibration
		std::cout << "\n============== START CALIBRATION ==============\n"
				  << std::endl;

		calib(calib_params);
		long int a = calib_params[0];
		long int b = calib_params[1];

		std::cout << "l(t)= " << a << " * t + " << b << std::endl;

		std::cout << "\n============== CALIBRATION COMPLETE ==============\n"
				  << std::endl;

		// Check if it is correct
		std::cout << "\n============== CHECK CALIBRATION ==============\n"
				  << std::endl;

		unsigned int nLoopTest = run(10);

		std::cout << "Resultat: \n\n" << std::endl;
		std::cout << "Expected Loop number: " << 10 * a + b << std::endl;
		std::cout << "Actual Loop number: " << nLoopTest << std::endl;

		// Return
		return 0;
}
