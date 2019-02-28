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
	pthread_t posixId;
	pthread_attr_t posixAttr;

public:
	PosixThread();
	PosixThread(pthread_t posixId);
	~PosixThread();
	void start(void* (*threadFunc) (void*), void* threadArg);
	void join();
	bool join(double timeout_ms);
	bool setScheduling(int schedPolicy, int priority);
	bool getScheduling(int* p_schedPolicy=nullptr, int* p_priority=nullptr);
};

#endif