/**
 * @file Countdown.h
 * @brief Implementation of the Countdown class
 */

#ifndef COUNTDOWN_INCLUDED
#define COUNTDOWN_INCLUDED

#include "PeriodicTimer.h"

/**
 * @brief A class that implements a countdown
 */
class Countdown : public PeriodicTimer {
private:
	/**
	 * @brief The counter for countdown
	 */
	int counter;

public:
	/**
	 * @brief Constructor
	 * 
	 * @param n the initial value of the counter
	 */
	Countdown(int n);

protected:
	/**
	 * @brief The callback for the underlying timer
	 */
	void callback();
};

#endif