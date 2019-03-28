/**
 * @file IncrThread.h
 * @brief Implementation of the IncrThread class for tutorial question 4a
 */

#ifndef INCR_THREAD_INCLUDED
#define INCR_THREAD_INCLUDED

#include "Thread.h"

/**
 * @brief A class that implements a Thread that performs
 * incrementations on a counter
 */
class IncrThread : public Thread
{

	private:
		/**
		 * @brief A pointer to the counter
		 */
		volatile double *p_counter;

		/**
		 * @brief The number of incrementations to do
		 */
		unsigned int loops;

	public:
		/**
		 * @brief SafeIncrThread Constructor
		 *
		 * @param p_counter pointer to the global counter
		 * @param nLoops number of loops to perform
		 * @param sched_policy shceduling policy of the process
		 */
		IncrThread(volatile double *p_counter, unsigned int nLoops,
				   int schedPolicy);

		/**
		 * @brief The copy constructor
		 *
		 * @param other The other Thread that we want to copy
		 */
		IncrThread(IncrThread const &other);

		/**
		 * @brief Default destructor
		 * It is not required.
		 */
		~IncrThread();

		/**
		 * @brief The increment function
		 */
		void run();
};

#endif