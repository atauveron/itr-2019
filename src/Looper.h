/**
 * @file Looper.h
 * @brief Implementation of the Looper class
 */

#ifndef LOOPER_INCLUDED
#define LOOPER_INCLUDED

#include <limits>

/**
 * @brief A class that implements a Looper system
 */
class Looper {

private:
	volatile bool doStop = false;
	double iLoop = 0;

public:
	double runLoops(double nLoops = std::numeric_limits<double>::max());
	double getSamples();
	double stopLoop();
};

#endif