#include "Timer.h"

#include <ctime>
#include <csignal>

Timer::Timer() {
	struct sigaction sa;
	sa.sa_sigaction = call_callback;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);

	struct sigevent sev;
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = this;
	
	timer_create(CLOCK_REALTIME, &sev, &tid);
}

Timer::~Timer() { timer_delete(tid); }

void Timer::stop() {
	itimerspec its;
	its.it_value = {0, 0};
	timer_settime(tid, 0 ,&its, NULL);
}

void Timer::call_callback(int sig, siginfo_t *si, void *user) {
	Timer * timer = reinterpret_cast<Timer *>(si->si_value.sival_ptr);
	timer->callback();
	return;
}