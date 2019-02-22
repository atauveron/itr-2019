/* \file timespec.h
 * \brief Implementations of operations on the Posix data structure timespec
 */

#ifndef TIMESPEC_INCLUDED
#define TIMESPEC_INCLUDED

#include <ctime>

double timespec_to_ms(const timespec &time_ts);

timespec timespec_from_ms(const double &time_ms);

timespec timespec_now();

timespec timespec_negate(const timespec &time_ts);

timespec timespec_add(const timespec &time1_ts, const timespec &time2_ts);

timespec timespec_subtract(const timespec &time1_ts, const timespec &time2_ts);

timespec timespec_wait(const timespec &delay_ts);

inline timespec operator-(const timespec &time_ts) {
  return timespec_negate(time_ts);
}

inline timespec operator+(const timespec &time1_ts, const timespec &time2_ts) {
  return timespec_add(time1_ts, time2_ts);
}

inline timespec operator-(const timespec &time1_ts, const timespec &time2_ts) {
  return timespec_subtract(time1_ts, time2_ts);
}

inline timespec &operator+=(timespec &time_ts, const timespec &delay_ts) {
  time_ts = timespec_add(time_ts, delay_ts);
  return time_ts;
}

inline timespec &operator-=(timespec &time_ts, const timespec &delay_ts) {
  time_ts = timespec_subtract(time_ts, delay_ts);
  return time_ts;
}

inline bool operator==(const timespec &time1_ts, const timespec &time2_ts) {
  return time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec &&
         time2_ts.tv_nsec;
}

inline bool operator!=(const timespec &time1_ts, const timespec &time2_ts) {
  return !(time1_ts == time2_ts);
}
inline bool operator<(const timespec &time1_ts, const timespec &time2_ts) {
  return (time1_ts - time2_ts).tv_sec < 0;
}

inline bool operator>(const timespec &time1_ts, const timespec &time2_ts) {
  return (time1_ts - time2_ts).tv_sec > 0;
}

#endif