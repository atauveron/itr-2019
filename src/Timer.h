/**
 * @file Timer.h
 * @brief Implementation of the Timer class
 */

#ifndef TIMER_INCLUDED
#define TIMER_INCLUDED

#include <ctime>
#include <csignal>

/**
 * @brief A class that implements a timer
 */
class Timer {
protected:
	timer_t tid;

public:
	Timer();
	~Timer();
	void stop();
	virtual void start(double duration_ms);

protected:
	virtual void callback() = 0;

private:
	static void call_callback(int sig, siginfo_t *si, void *user);
};

#endif