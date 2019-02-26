/**
 * @file Chrono.h
 * @brief Implementation of the Chrono class
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
   * @brief The start time
   */
  timespec startTime_;
  /**
   * @brief The stop time
   */
  timespec stopTime_;

public:
  /**
   * @brief Default constructor
   * This method constructs a chronometer and starts it.
   */
  Chrono();
  /**
   * @brief Stop the chronometer
   * This sets the stop time of the chronometer.
   */
  void stop();
  /**
   * @brief Restart the chronometer
   * This resets the start time of the chronometer.
   */
  void restart();
  /**
   * @brief Check whether a chronometer is active
   * @return a boolean indicating whether the chronometer is active
   */
  bool isActive();
  /**
   * @brief Access the start time
   * Whether a timer is active is determined by comparing its start time and
   * stop time: if they are equal, the chronometer is inactive, otherwise it is
   * active.
   * @return the start time (in ms)
   */
  double startTime();
  /**
   * @brief Access the stop time
   * Note that, while a chronometer is active, the stop time is equal to the
   * start time.
   * @return the stop time (in ms)
   */
  double stopTime();
  /**
   * @brief Time elapsed since starting (or restarting) the chronometer
   * @return the time elapsed since the start time (in ms)
   */
  double lap();
};

#endif