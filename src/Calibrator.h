/**
 * @file Calibrator.h
 * @brief Implementation of the Calibrator class
 */

#ifndef CALIBRATOR_INCLUDED
#define CALIBRATOR_INCLUDED

#include <array>
#include <vector>

#include "Looper.h"
#include "PeriodicTimer.h"

/**
 * @brief A class that implements a calibrator for the loop
 */
class Calibrator : PeriodicTimer {

private:
	double a;
	double b;
	Looper *looper = nullptr;
	std::vector<double> samples{};
	unsigned counter;

public:
	/**
	 * @brief Constructor
	 *
	 * @param samplingPeriod_ms the sampling period for calibration (in ms)
	 * @param nSamples the number of samples to use for calibration
	 */
	Calibrator(double samplingPeriod_ms, unsigned nSamples);
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
};

#endif