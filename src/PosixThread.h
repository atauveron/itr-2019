/**
 * @file PosixThread.h
 * @brief Implementation of the PosixThread class
 */

#ifndef POSIX_THREAD_INCLUDED
#define POSIX_THREAD_INCLUDED

#include <pthread.h>

/**
 * @brief A class that implements a POSIX Thread
 */
class PosixThread {

public:
	// TODO: UML WTF ???
	// class Exception

private:
	/**
	 * @brief the id of the underlying Posix thread
	 */
	pthread_t posixId;
	/**
	 * @brief the attributes of the underlying Posix thread
	 */
	pthread_attr_t posixAttr;

public:
	/**
	 * @brief Default constructor
	 */
	PosixThread();
	/**
	 * @brief Constructor from an existing pthread
	 * 
	 * @param posixId the identifier of the pthread from which to construct the object
	 */
	PosixThread(pthread_t posixId);
	/**
	 * @brief Destructor
	 */
	~PosixThread();
	/**
	 * @brief Run a function in the thread
	 * 
	 * @param threadFunc the function to run
	 * @param threadArg the arguments for the function to run
	 */
	void start(void *(*threadFunc)(void *), void *threadArg);
	/**
	 * @brief Join a thread
	 */
	void join();
	/**
	 * @brief Join a thread (with a timeout)
	 * If the timeout delay elapses before the thread joins, the thread id killed.
	 * 
	 * @param timeout_ms the timeout delay (in ms)
	 * @return `true` if the thread was joined successfully, `false` otherwise
	 */
	bool join(double timeout_ms);
	/**
	 * @brief Set the scheduling policy of the thread
	 * 
	 * @param schedPolicy the scheduling policy for the thread
	 * @param priority the priority of the thread
	 * @return `true` if the operation succeeds, `false` otherwise
	 */
	bool setScheduling(int schedPolicy, int priority);
	/**
	 * @brief Get the scheduling policy of the thread
	 * 
	 * @param schedPolicy the current scheduling policy for the thread
	 * @param priority the current priority of the thread
	 * @return `true` if the operation succeeds, `false` otherwise
	 */
	bool getScheduling(int *p_schedPolicy = nullptr, int *p_priority = nullptr);
};

#endif