/**
 * @file Chrono.h
 * @brief Implementations of the Chrono class
 */

#ifndef CHRONO_INCLUDED
#define CHRONO_INCLUDED

#include <ctime>

#include "timespec.h"

/**
 * @brief A class that implements a chronometer
 */
class Chrono {
private:
  /**
   * @brief the start time
   */
  timespec startTime_;
  /**
   * @brief the stop time
   */
  timespec stopTime_;

public:
  Chrono();
  void stop();
  void restart();
  bool isActive();
  double startTime();
  double stopTime();
  double lap();
};

#endif