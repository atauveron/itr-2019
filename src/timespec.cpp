#include "timespec.h"

double timespec_to_ms(const timespec &time_ts) {
	return time_ts.tv_sec * 1000 + time_ts.tv_nsec / 1000000;
}

timespec timespec_from_ms(const double &time_ms) {
	timespec time_ts;
	time_ts.tv_sec = time_ms / 1000;
	time_ts.tv_nsec = (long)(time_ms - time_ts.tv_sec * 1000) * 1000000;
	return time_ts;
}

timespec timespec_now() {
	timespec time_ts;
	clock_gettime(CLOCK_REALTIME, &time_ts);
	return time_ts;
}

timespec timespec_negate(const timespec &time_ts) {
	timespec negTime_ts;
	if (time_ts.tv_nsec == 0) {
		negTime_ts.tv_sec = -time_ts.tv_sec;
		negTime_ts.tv_nsec = 0;
	} else {
		negTime_ts.tv_nsec = 1000000000 - time_ts.tv_nsec;
		negTime_ts.tv_sec = -(time_ts.tv_sec + 1);
	}
	return negTime_ts;
}

timespec timespec_add(const timespec &time1_ts, const timespec &time2_ts) {
	timespec time_ts;
	long nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
	if (nsec > 1000000000) {
		time_ts.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec + 1;
		time_ts.tv_nsec = nsec - 1000000000;
	} else {
		time_ts.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
		time_ts.tv_nsec = nsec;
	}
	return time_ts;
}

timespec timespec_subtract(const timespec &time1_ts, const timespec &time2_ts) {
	return timespec_add(time1_ts, timespec_negate(time2_ts));
}

timespec timespec_wait(const timespec &delay_ts) {
	timespec remain{};
	nanosleep(&delay_ts, &remain);
	return remain;
}
