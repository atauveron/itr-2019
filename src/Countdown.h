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
	int counter;

public:
	Countdown(int n);

protected:
	void callback();
};

#endif