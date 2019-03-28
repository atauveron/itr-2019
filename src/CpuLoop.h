/**
 * @file CpuLoop.h
 * @brief Implementation of the CpuLoop class
 */

#ifndef CPULOOP_INCLUDED
#define CPULOOP_INCLUDED

#include "Calibrator.h"
#include "Looper.h"

/**
 * @brief A class that implements a CPU Loop
 */
class CpuLoop : public Looper
{
	private:
		/**
		 * @brief The calibrator used to calibrate the Looper
		 */
		Calibrator &calibrator;

	public:
		/**
		 * @brief Constructor
		 *
		 * @param calibrator_ reference to the calibrator used to calibrate the
		 * Looper
		 */
		CpuLoop(Calibrator &calibrator_);

		/**
		 * @brief Runs a number of loop based on the calibration
		 *
		 * @param duration_ms the duration of the runLoop execution
		 */
		void runTime(double duration_ms);
};

#endif