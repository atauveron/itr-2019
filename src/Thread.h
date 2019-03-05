/**
 * @file Thread.h
 * @brief Implementation of the Thread class
 */

#ifndef THREAD_INCLUDED
#define THREAD_INCLUDED

#include "Chrono.h"
#include "PosixThread.h"

/**
 * @brief A class that implements a Thread
 */
class Thread : public PosixThread {

private:
	/**
	 * @brief A Chronometer object
	 */
	Chrono chrono;

public:
	/**
	 * @brief Default constructor
	 * It is not required.
	 */
	Thread();
	/**
	 * @brief Default destructor
	 * It is not required.
	 */
	~Thread();
	void start();
	double startTime_ms();
	double stopTime_ms();
	double execTime_ms();
	static void sleep_ms(double delay_ms);

protected:
	void virtual run() = 0;

private:
	static void *call_run(void *v_thread);
};

#endif