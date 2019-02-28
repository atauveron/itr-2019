#include "PeriodicTimer.h"

#include <ctime>

#include "timespec.h"

void PeriodicTimer::start(double duration_ms) {
	itimerspec its;
	timespec tspec = timespec_from_ms(duration_ms);

	its.it_value = {tspec.tv_sec, tspec.tv_nsec};
	its.it_interval = {tspec.tv_sec, tspec.tv_nsec};
	
	timer_settime(tid, 0, &its, NULL);
}