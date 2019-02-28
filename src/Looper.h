/**
 * @file Looper.h
 * @brief Implementation of the Looper class
 */

#ifndef LOOPER_INCLUDED
#define LOOPER_INCLUDED

#include <cfloat>

/**
 * @brief A class that implements a Looper system
 */
class Looper {

private:
	bool doStop;
	double iLoop;

public:
	double runLoops(double nLoops=DBL_MAX);
	double getSamples();
	double stopLoop();
};

#endif