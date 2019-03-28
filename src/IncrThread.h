/**
 * @file IncrThread.h
 * @brief Implementation of the IncrThread class for tutorial question 4a
 */

// TODO UPDATE DOC

#ifndef INCR_THREAD_INCLUDED
#define INCR_THREAD_INCLUDED

#include "Thread.h"

/**
 * @brief A class that increments a counter (derived from our custom Thread
 * class)
 */
class IncrThread : public Thread {

private:
	/**
	 * @brief A pointer to the counter to increment
	 */
	volatile double *p_counter;
	/**
	 * @brief A Chronometer object
	 */
	unsigned int loops;

public:
	/**
	 * @brief Constructor
	 *
	 * @param p_counter a pointer to the counter to increment
	 * @param nLoops the number of loops to perform
	 * @param schedPolicy the thread's scheduling policy
	 */
	IncrThread(volatile double *p_counter, unsigned int nLoops, int schedPolicy);

	/**
	 * @brief Copy constructor
	 */
	IncrThread(IncrThread const &);

	/**
	 * @brief Default destructor
	 * It is not required.
	 */
	~IncrThread();

	void run();
};

#endif