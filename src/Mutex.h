/**
 * @file Mutex.h
 * @brief Implementation of the Mutex class
 */

#ifndef MUTEX_INCLUDED
#define MUTEX_INCLUDED

#include <pthread.h>

/**
 * @brief A class that implements a mutex
 */
class Mutex {

	public:
		class Lock {
			private:
				Mutex &mtx;

			public:
				Lock(Mutex &m);
				Lock(Mutex &m, double timeout_ms);
				~Lock();
				void wait();
				bool wait(double timeout_ms);
				void notify();
				void notifyAll();
		};

	private:
		pthread_mutex_t posixId;
		pthread_cond_t posixCondId;

	public:
		Mutex();
		~Mutex();

	private:
		void lock();
		bool lock(double timeout_ms);
		bool trylock();
		void unlock();
};

#endif