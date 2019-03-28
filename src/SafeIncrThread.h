/**
 * @file SafeIncrThread.h
 * @brief Implementation of the SafeIncrThread class for tutorial question 4a
 */

#ifndef SAFE_INCR_THREAD_INCLUDED
#define SAFE_INCR_THREAD_INCLUDED

#include "Thread.h"

/**
 * @brief A class that increments a thread-safe counter (derived from our custom
 * Thread class)
 */
class SafeIncrThread : public Thread
{

	private:
		/**
		 * @brief A pointer to the counter to increment
		 */
		volatile double *p_counter;
		/**
		 * @brief A Chronometer object
		 */
		unsigned int loops;
		Mutex *		 mutex;

	public:
		/**
		 * @brief Constructor
		 *
		 * @param p_counter a pointer to the counter to increment
		 * @param nLoops the number of loops to perform
		 * @param schedPolicy the thread's scheduling policy
		 * @param mtx the mutex to use for thread-safety
		 */
		SafeIncrThread(volatile double *p_counter, unsigned int nLoops,
					   int schedPolicy, Mutex *mtx);

		/**
		 * @brief Copy constructor
		 */
		SafeIncrThread(SafeIncrThread const &);

		/**
		 * @brief Default destructor
		 * It is not required.
		 */
		~SafeIncrThread();

		void run();
};

#endif