/**
 * @file Mutex.h
 * @brief Implementation of the Mutex class
 */

#ifndef MUTEX_INCLUDED
#define MUTEX_INCLUDED

#include <exception>
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
	class Lock;

	/**
	 * @brief A class to implement the try-lock functionality for the Mutex class
	 */
	class TryLock;

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
	 * @brief Method to acquire the mutex (for use by Lock nested class)
	 */
	void lock();
	/**
	 * @brief Method to acquire the mutex with timeout (for use by Lock nested class)
	 */
	bool lock(double timeout_ms);
	/**
	 * @brief Method to try to acquire the mutex (for use by TryLock nested class)
	 */
	bool trylock();
	/**
	 * @brief Method to release the mutex (for use by Lock and TryLock nested class)
	 */
	void unlock();
};

/**
 * @brief A class to implement the lock functionality for the Mutex class
 *
 * This enables exception-safe locking and unlocking of mutexes.
 */
class Mutex::Lock {
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

protected:
	/**
	 * @brief A constructor to be used by the TryLock child class
	 *
	 * @param m the mutex to lock (passed by reference)
	 * @param[out] whether or not the attempt to lock succeeded
	 */
	Lock(Mutex &m, bool &status);

public:
	/**
	 * @brief An exception class in case of timeout while attempting to lock
	 */
	class TimeoutException : std::exception {
	public:
		const char *what() const noexcept;
	};
};

/**
 * @brief A class to implement the try-lock functionality for the Mutex class
 */
class Mutex::TryLock : public Lock {
private:
	/**
	 * @brief Whether the lock operation succeeded
	 */
	bool success;

public:
	/**
	 * @brief Constructor
	 */
	TryLock(Mutex &m);
	/**
	 * @brief Destructor
	 */
	~TryLock();

	/**
	 * @brief An exception class in case of failure to lock
	 */
	class TryLockException : std::exception {
	public:
		const char *what() const noexcept;
	};
};

#endif