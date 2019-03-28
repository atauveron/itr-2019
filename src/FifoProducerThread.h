/**
 * @file FifoProducerThread.h
 * @brief Implementation of the FifoProducerThread class for tutorial
 * question 4d
 */

#ifndef FIFO_PROD_THREAD_INCLUDED
#define FIFO_PROD_THREAD_INCLUDED

#include "Fifo.hpp"
#include "Mutex.h"
#include "Thread.h"

/**
 * @brief A class that implements a Thread that produces tokens through a
 * Fifo
 */
class FifoProducerThread : public Thread
{

	private:
		/**
		 * @brief A pointer to a Fifo
		 */
		Fifo<int> *fifo;

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
		 * @brief FifoProducerThread Constructor
		 *
		 * @param p_counter pointer to the global counter
		 * @param nLoops number of loops to perform
		 * @param sched_policy shceduling policy of the process
		 */
		FifoProducerThread(Fifo<int> *p_counter, unsigned int nTokens);

		/**
		 * @brief The copy constructor
		 *
		 * @param other The other Thread that we want to copy
		 */
		FifoProducerThread(FifoProducerThread const &other);

		/**
		 * @brief Default destructor
		 * It is not required.
		 */
		~FifoProducerThread();

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