/**
 * @file Mutex.h
 * @brief Implementation of the Mutex class
 */

#ifndef MUTEX_INCLUDED
#define MUTEX_INCLUDED

#include <pthread.h>

/**
 * @brief A class that implements a mutex
 *
 * This class relies on Posix mutex and provides a high-level interface.
 * The mutex is locked and unlocked through the nested `Lock` class.
 */
class Mutex {

public:
	/**
	 * @brief A class to implement the lock functionality for the Mutex class
	 *
	 * This enables exception-safe locking and unlocking of mutexes.
	 */
	class Lock {
	private:
		/**
		 * @brief A reference to the mutex object we operate on.
		 */
		Mutex &mtx;

	public:
		/**
		 * @brief Constructor (acquire the mutex)
		 *
		 * @param m the mutex to lock (passed by reference)
		 */
		Lock(Mutex &m);
		/**
		 * @brief Constructor (acquire the mutex)
		 *
		 * @param m the mutex to lock  (passed by reference)
		 * @param timeout_ms the maximum time to wait to acquire the mutex
		 */
		Lock(Mutex &m, double timeout_ms);
		/**
		 * @brief Destructor (release the mutex)
		 */
		~Lock();
		void wait();
		bool wait(double timeout_ms);
		void notify();
		void notifyAll();
	};

private:
	/**
	 * @brief The underlying Posix mutex
	 */
	pthread_mutex_t posixId;
	/**
	 * @brief The underlying Posix condition variable
	 */
	pthread_cond_t posixCondId;

public:
	/**
	 * @brief Constructor
	 */
	Mutex();
	/**
	 * @brief Destructor
	 */
	~Mutex();

private:
	/**
	 * Method to acquire the mutex (for use by Lock nested class)
	 */
	void lock();
	/**
	 * Method to acquire the mutex with timeout (for use by Lock nested class)
	 */
	bool lock(double timeout_ms);
	/**
	 * Method to try to acquire the mutex (for use by Lock nested class)
	 */
	bool trylock();
	/**
	 * Method to release the mutex (for use by Lock nested class)
	 */
	void unlock();
};

#endif