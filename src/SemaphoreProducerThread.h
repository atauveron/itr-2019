/**
 * @file SemaphoreProducerThread.h
 * @brief Implementation of the SemaphoreProducerThread class for tutorial
 * question 4c
 */

#ifndef SEM_PROD_THREAD_INCLUDED
#define SEM_PROD_THREAD_INCLUDED

#include "Semaphore.h"
#include "Thread.h"

/**
 * @brief A class that implements a Thread that produces tokens through a
 * semaphore
 */
class SemaphoreProducerThread : public Thread
{

	private:
		/**
		 * @brief A pointer to a semaphore
		 */
		Semaphore *semaphore;

		/**
		 * @brief The number of tokens to create
		 */
		unsigned int targetTokens;

		/**
		 * @brief The number of tokens produced
		 */
		unsigned int producedTokens;
		;

	public:
		/**
		 * @brief SemaphoreProducerThread Constructor
		 *
		 * @param p_counter pointer to the global counter
		 * @param nLoops number of loops to perform
		 * @param sched_policy shceduling policy of the process
		 */
		SemaphoreProducerThread(Semaphore *p_counter, unsigned int nTokens);

		/**
		 * @brief The copy constructor
		 *
		 * @param other The other Thread that we want to copy
		 */
		SemaphoreProducerThread(SemaphoreProducerThread const &other);

		/**
		 * @brief Default destructor
		 * It is not required.
		 */
		~SemaphoreProducerThread();

		/**
		 * @brief The produce function
		 */
		void run();

		/**
		 * @brief Return the number of produced tokens
		 */
		int tokens();
};

#endif