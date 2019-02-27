/**
 * @file PeriodicTimer.h
 * @brief Implementation of the PeriodicTimer class
 */

#ifndef PERIODIC_TIMER_INCLUDED
#define PERIODIC_TIMER_INCLUDED

#include <ctime>
#include <csignal>

/**
 * @brief A class that implements a periodic timer
 */
class PeriodicTimer : Timer {

public:
  void start(double duration_ms);
};

#endif