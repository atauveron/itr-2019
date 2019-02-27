/**
 * @file CpuLoop.h
 * @brief Implementation of the CpuLoop class
 */

#ifndef CPULOOP_INCLUDED
#define CPULOOP_INCLUDED

#include "Calibrator.h"

/**
 * @brief A class that implements a cpu Loop
 */
class CpuLoop {

public:
  CpuLoop(Calibrator *calibrator);
  void runTime(double duration_ms);
};

#endif