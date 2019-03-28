/**
 * @file Semaphore.h
 * @brief Implementation of the Semaphore class
 */

#ifndef SEMAPHORE_INCLUDED
#define SEMAPHORE_INCLUDED

#include "Mutex.h"

#include <limits>
#include <pthread.h>

/**
 * @brief A class that implements a semaphore
 *
 * This class relies on the Mutex class, which itself relies on a Posix
 * semaphore.
 */
class Semaphore
{

	private:
		/**
		 * @brief The number of tokens currently available
		 */
		unsigned int counter;

		/**
		 * @brief The maximum number of tokens a Semaphore can own
		 */
		unsigned int maxCounter;

		/**
		 * @brief A mutex to ensure the semaphore is thread-safe
		 */
		Mutex mtx;

	public:
		/**
		 * @brief Constructor
		 */
		Semaphore(
			unsigned int initCount = 0,
			unsigned int maxCount  = std::numeric_limits<unsigned int>::max());

		/**
		 * @brief Destructor
		 */
		~Semaphore();

		/**
		 * @brief A method to give the semaphore a token
		 */
		void give();

		/**
		 * @brief A method to take a token from the semaphore
		 */
		void take();

		/**
		 * @brief A method to take a token from the semaphore, with a timeout
		 *
		 * @param timeout_ms the timeout for taking a token
		 * @return `true` if a token was succesfully taken, `false` otherwise.
		 */
		bool take(double timeout_ms);
};

#endif