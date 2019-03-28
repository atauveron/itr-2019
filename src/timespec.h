/**
 * @file timespec.h
 * @brief Implementations of various operations on the Posix structure timespec
 */

#ifndef TIMESPEC_INCLUDED
#define TIMESPEC_INCLUDED

#include <ctime>

/**
 * @brief Convert a timespec structure to miliseconds
 * Note the operation may involve a loss of precision (since timespec is
 * accurate down to nanoseconds).
 *
 * @param time_ts the timespec to convert
 * @return the number of miliseconds
 */
double timespec_to_ms(const timespec &time_ts);

/**
 * @brief Convert miliseconds to a timespec structure
 * This operation does not involve any loss if precision.
 *
 * @param time_ms the number of miliseconds to convert
 * @return a timespec structure
 */
timespec timespec_from_ms(const double &time_ms);

/**
 * @brief Return the current time
 * This function returns a timespec structure containing the current time
 * (obtained using the clock `CLOCK_REALTIME`).
 *
 * @return a timespec structure
 */
timespec timespec_now();

/**
 * @brief Return the opposite of a time
 * This function returns the opposite of the time provided as argument (as a
 * timespec structure).
 *
 * @param time_ts the timespec structure to inverse
 * @return a timespec structure (opposite of @p time_ts)
 */
timespec timespec_negate(const timespec &time_ts);

/**
 * @brief Return the sum of two times
 * This function returns the sum of the two times provided as argument (as
 * timespec structures).
 *
 * @param time1_ts the first timespec structure to add
 * @param time2_ts the second timespec structure to add
 * @return a timespec structure (@p time1_ts + @p time2_ts)
 */
timespec timespec_add(const timespec &time1_ts, const timespec &time2_ts);

/**
 * @brief Return the difference of two times
 * This function returns the difference of the two times provided as argument
 * (as timespec structures).
 *
 * @param time1_ts the timespec structure from which to substract
 * @param time2_ts the timespec structure to substract
 * @return a timespec structure (@p time1_ts - @p time2_ts)
 */
timespec timespec_subtract(const timespec &time1_ts, const timespec &time2_ts);

/**
 * @brief Wait for a specified time
 * This function causes the thread to sleep (pause) for a specified time.
 *
 * @param delay_ts a timespec structure representing the time to wait for
 * @return the remaining time to wait for
 */
timespec timespec_wait(const timespec &delay_ts);

/**
 * @brief The `-` (inverse) operator for timespec
 * This function returns the opposite of the time provided as argument (as a
 * timespec structure).
 *
 * @param time_ts the timespec structure to inverse
 * @return a timespec structure (opposite of @p time_ts)
 */
inline timespec operator-(const timespec &time_ts)
{
		return timespec_negate(time_ts);
}

/**
 * @brief The `+` (addition) operator for timespec
 * This function returns the sum of the two times provided as argument (as
 * timespec structures).
 *
 * @param time1_ts the first timespec structure to add
 * @param time2_ts the second timespec structure to add
 * @return a timespec structure (@p time1_ts + @p time2_ts)
 */
inline timespec operator+(const timespec &time1_ts, const timespec &time2_ts)
{
		return timespec_add(time1_ts, time2_ts);
}

/**
 * @brief The `-` (substraction) operator for timespec
 * This function returns the difference of the two times provided as argument
 * (as timespec structures).
 *
 * @param time1_ts the timespec structure from which to substract
 * @param time2_ts the timespec structure to substract
 * @return a timespec structure (@p time1_ts - @p time2_ts)
 */
inline timespec operator-(const timespec &time1_ts, const timespec &time2_ts)
{
		return timespec_subtract(time1_ts, time2_ts);
}

/**
 * @brief The `+=` (incrementation) operator for timespec
 * This function returns the sum of the two times provided as argument (as
 * timespec structures).
 * @p time_ts is modified in place.
 *
 * @param time_ts the timespec structure to increment
 * @param delay_ts the timespec structure to add (ie, the value of the
 * increment)
 * @return the incremented timespec structure @p time_ts
 */
inline timespec &operator+=(timespec &time_ts, const timespec &delay_ts)
{
		time_ts = timespec_add(time_ts, delay_ts);
		return time_ts;
}

/**
 * @brief The `-=` (decrementation) operator for timespec
 * This function returns the difference of the two times provided as argument
 * (as timespec structures).
 * @p time_ts is modified in place.
 *
 * @param time_ts the timespec structure to decrement
 * @param delay_ts the timespec structure to substract (ie, the value of the
 * decrement)
 * @return the decremented timespec structure @p time_ts
 */
inline timespec &operator-=(timespec &time_ts, const timespec &delay_ts)
{
		time_ts = timespec_subtract(time_ts, delay_ts);
		return time_ts;
}

/**
 * @brief The `==` (equal) operator for timespec
 * This function returns a boolean indicating whether ot nor the two arguments
 * represent the same value.
 *
 * @param time1_ts the first timespec structure to compare
 * @param time2_ts the second timespec structure to compare
 * @return a boolean indicating whether the two values are equal
 */
inline bool operator==(const timespec &time1_ts, const timespec &time2_ts)
{
		return time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec &&
			   time2_ts.tv_nsec;
}

/**
 * @brief The `!=` (different) operator for timespec
 * This function returns a boolean indicating whether ot nor the two arguments
 * represent different values.
 *
 * @param time1_ts the first timespec structure to compare
 * @param time2_ts the second timespec structure to compare
 * @return a boolean indicating whether the two values are different
 */
inline bool operator!=(const timespec &time1_ts, const timespec &time2_ts)
{
		return !(time1_ts == time2_ts);
}

/**
 * @brief The `<` (less than) operator for timespec
 * This function returns a boolean indicating whether ot nor the first argument
 * is strictly less than the second.
 *
 * @param time1_ts the first timespec structure to compare
 * @param time2_ts the second timespec structure to compare
 * @return a boolean indicating whether @p time1_ts < @p time2_ts
 */
inline bool operator<(const timespec &time1_ts, const timespec &time2_ts)
{
		return (time1_ts - time2_ts).tv_sec < 0;
}

/**
 * @brief The `>` (greater than) operator for timespec
 * This function returns a boolean indicating whether ot nor the first argument
 * is strictly greater than the second.
 *
 * @param time1_ts the first timespec structure to compare
 * @param time2_ts the second timespec structure to compare
 * @return a boolean indicating whether @p time1_ts > @p time2_ts
 */
inline bool operator>(const timespec &time1_ts, const timespec &time2_ts)
{
		return (time1_ts - time2_ts).tv_sec > 0;
}

#endif