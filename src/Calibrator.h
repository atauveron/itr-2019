/**
 * @file Calibrator.h
 * @brief Implementation of the Calibrator class
 */

#ifndef CALIBRATOR_INCLUDED
#define CALIBRATOR_INCLUDED

#include "Looper.h"
#include "PeriodicTimer.h"

#include <array>
#include <vector>

/**
 * @brief A class that implements a calibrator for the loop
 */
class Calibrator : PeriodicTimer
{

	private:
		/**
		 * @brief slope of the linear regression
		 */
		double a;

		/**
		 * @brief offset of the linear regression
		 */
		double b;

		/**
		 * @brief Looper instance used for calibration
		 */
		Looper *looper = nullptr;

		/**
		 * @brief Samples collected for linear regression
		 */
		std::vector<double> samples{};

		/**
		 * @brief counter
		 */
		unsigned int counter;

	public:
		/**
		 * @brief Constructor
		 *
		 * @param samplingPeriod_ms the sampling period for calibration (in ms)
		 * @param nSamples the number of samples to use for calibration
		 */
		Calibrator(double samplingPeriod_ms, unsigned int nSamples);

		/**
		 * @brief Convert a duration to a number of loops
		 * This method uses the data obtained when constructing the calibrator.
		 *
		 * @param duration_ms the duration to convert (in ms)
		 * @return the number of loops
		 */
		double nLoops(double duration_ms);

	protected:
		/**
		 * @brief The callback for the timer (used for calibration)
		 */
		void callback();

	private:
		/**
		 * @brief A function that performs a linear regression to find
		 * linear coefficient
		 *
		 * @param values The slope `a` and the offset `b`
		 * @param x Array of x-axis values
		 * @param x Array of y-axis values
		 * @param N Size of the arrays
		 */
		void regressionError(double *values, std::vector<double> Y, unsigned N,
							 double dx);
};

#endif