/**
 * @file PeriodicTimer.h
 * @brief Implementation of the PeriodicTimer class
 */

#ifndef PERIODIC_TIMER_INCLUDED
#define PERIODIC_TIMER_INCLUDED

#include "Timer.h"

/**
 * @brief A class that implements a periodic timer
 */
class PeriodicTimer : public Timer
{

	public:
		/**
		 * @brief Start a periodic timer
		 *
		 * @param duration_ms The interval of the timer
		 */
		void start(double duration_ms);
};

#endif