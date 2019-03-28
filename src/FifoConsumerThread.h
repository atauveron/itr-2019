/**
 * @file FifoConsumerThread.h
 * @brief Implementation of the FifoConsumerThread class for tutorial
 * question 4d
 */

#ifndef FIFO_CONS_THREAD_INCLUDED
#define FIFO_CONS_THREAD_INCLUDED

#include "Fifo.hpp"
#include "Thread.h"

/**
 * @brief A class that implements a Thread that consumes tokens through a
 * Fifo
 */
class FifoConsumerThread : public Thread
{

	private:
		/**
		 * @brief A pointer to a Fifo
		 */
		Fifo<int> *fifo;

		/**
		 *  @biref Mutex used for the Fifo
		 */
		Mutex *mutex;

		/**
		 * @brief The number of tokens produced
		 */
		unsigned int consumedTokens;

	public:
		/**
		 * @brief FifoConsumerThread Constructor
		 *
		 * @param p_counter pointer to the global counter
		 * @param nLoops number of loops to perform
		 * @param sched_policy shceduling policy of the process
		 */
		FifoConsumerThread(Fifo<int> *p_fifo, Mutex *mtx);

		/**
		 * @brief The copy constructor
		 *
		 * @param other The other Thread that we want to copy
		 */
		FifoConsumerThread(FifoConsumerThread const &other);

		/**
		 * @brief Default destructor
		 * It is not required.
		 */
		~FifoConsumerThread();

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