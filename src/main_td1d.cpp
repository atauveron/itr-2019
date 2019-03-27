/**
 * @file main_td1c.cpp
 * @brief Main file for tutorial question 1c
 */
#include <climits>
#include <csignal>
#include <ctime>
#include <iostream>
#include <string>

#include "timespec.h"

/**
 * @brief A structure to wrap the data sent to the timer
 */
struct StopData {
    /// A boolean indicating whether incrementation of the counter should stop
    volatile bool stop;
};

/**
 * @brief A function that performs a linear regression to find
 * linear coefficient
 *
 * @param values The slope `a` and the offset `b`
 * @param x Array of x-axis values
 * @param x Array of y-axis values
 * @param N Size of the arrays
 */
void regressionError(double *values, double *X, double *Y, int N) {
    double xMean = 0;
    double yMean = 0;
    double xyError = 0;
    double squareXError = 0;

    // Compute Mean
    for (int i = 0; i < N; ++i) {
	xMean += X[i];
	yMean += Y[i];
    }

    xMean /= N;
    yMean /= N;

    // Compute Mean Square Error and XY Error to deduce slope
    for (int i = 0; i < N; ++i) {
	std::cout << xyError << " " << squareXError << std::endl;
	xyError += (xMean - X[i]) * (yMean - Y[i]);
	squareXError += (xMean - X[i]) * (xMean - X[i]);
    }

    double slope = xyError / squareXError;
    double offset = yMean - slope * xMean;
    values[0] = slope;
    values[1] = offset;

    // Return
    return;
}

/**
 * @brief A handler function for the timer
 * This function sets the boolean in structure of type StopData (passed via @p
 * si) to false.
 *
 * @param sig
 * @param si
 */
void handler(int, siginfo_t *si, void *) {
    StopData *stop = reinterpret_cast<StopData *>(si->si_value.sival_ptr);
    stop->stop = true;
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
double incr(unsigned int nLoops, double *pCounter, volatile bool *pStop) {
    double i;
    for (i = 0; i < nLoops; ++i) {
	if (*pStop) {
	    break;
	}
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
double run(long int delay_s) {
    unsigned int nLoops(UINT_MAX);
    double counter(0);
    StopData stop{false};

    // Timer
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &stop;

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid);
    itimerspec its;
    its.it_value = {delay_s, 0};
    its.it_interval = {0, 0};
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
 * @brief A function that run several iterations of `run`
 * to find the linear coefficient through linear regression
 *
 * @param params  The coefficients `a` & `b` for the linear relation
 * @param N The number of points wanted
 */
void calib(double *params, int N) {

    double x[N];
    double y[N];

    // Run for a N test
    for (int i = 1; i <= N; ++i) {
	x[i] = i;
	y[i] = run(i);
    }

    // Compute parameters from Mean Sqaure Error
    regressionError(params, x, y, N);

    // Return
    return;
}

int main() {

    double calib_params[2];

    // Start calibration
    std::cout << "\n ============== START CALIBRATION ============== \n"
	      << std::endl;
    calib(calib_params, 10);
    double a = calib_params[0];
    double b = calib_params[1];
    std::cout << "l(t)= " << a << " * t + " << b << std::endl;
    std::cout << "\n ============== CALIBRATION COMPLETE ============== \n"
	      << std::endl;

    // Check if it is correct
    std::cout << "\n ============== CHECK CALIBRATION ============== \n"
	      << std::endl;
    double nLoopTest = run(10);

    std::cout << "\n\n Résultat:" << std::endl;
    std::cout << "Expected Loop number: " << 10 * a + b << std::endl;
    std::cout << "Actual Loop number: " << nLoopTest << std::endl;

    // Return
    return 0;
}