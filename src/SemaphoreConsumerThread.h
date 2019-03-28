/**
 * @file SemaphoreConsumerThread.h
 * @brief Implementation of the SemaphoreConsumerThread class for tutorial
 * question 4c
 */

#ifndef SEM_CONS_THREAD_INCLUDED
#define SEM_CONS_THREAD_INCLUDED

#include "Semaphore.h"
#include "Thread.h"

/**
 * @brief A class that implements a Thread that consumes tokens through a
 * semaphore
 */
class SemaphoreConsumerThread : public Thread
{

	private:
		/**
		 * @brief A pointer to a semaphore
		 */
		Semaphore *semaphore;

		/**
		 * @brief The number of tokens produced
		 */
		unsigned int consumedTokens;

	public:
		/**
		 * @brief SemaphoreConsumerThread Constructor
		 *
		 * @param p_counter pointer to the global counter
		 * @param nLoops number of loops to perform
		 * @param sched_policy shceduling policy of the process
		 */
		SemaphoreConsumerThread(Semaphore *p_semaphore);

		/**
		 * @brief The copy constructor
		 *
		 * @param other The other Thread that we want to copy
		 */
		SemaphoreConsumerThread(SemaphoreConsumerThread const &other);

		/**
		 * @brief Default destructor
		 * It is not required.
		 */
		~SemaphoreConsumerThread();

		/**
		 * @brief The consume function
		 */
		void run();

		/**
		 * @brief Return the number of produced tokens
		 */
		int tokens();
};

#endif