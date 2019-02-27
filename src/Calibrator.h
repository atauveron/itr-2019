/**
 * @file Calibartor.h
 * @brief Implementation of the Calibrator class
 */

#ifndef CALIBRATOR_INCLUDED
#define CALIBRATOR_INCLUDED

#include "PeriodicTimer.h"

/**
 * @brief A class that implements a calibrator for the loop
 */
class Calibrator : PeriodicTimer {

private:
  double a;
  double b;

public:
  Calibrator(double samplingPeriod_ms, unsigned nSamples);
  double nLoops(double duration_ms);

protected:
  void callback();
};

#endif