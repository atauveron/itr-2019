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
class CpuLoop : public Looper {
private:
	Calibrator &calibrator;

public:
	CpuLoop(Calibrator &calibrator_);
	void runTime(double duration_ms);
};

#endif