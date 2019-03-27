/**
 * @file main_td1e.cpp
 * @brief Main file for tutorial question 1e
 * Most of the work for this question is in files `timespec.h` and
 * `timespec.cpp`.
 */
#include <ctime>
#include <iostream>

#include "timespec.h"

int main() {
    timespec time1_ts = timespec_from_ms(5000);
    timespec time2_ts = timespec_from_ms(5500);
    timespec now = timespec_now();

    timespec ressum = time1_ts + time2_ts;
    timespec resdiff = time1_ts - time2_ts;
    std::cout << "SUM: " << timespec_to_ms(ressum) << "ms | " << ressum.tv_sec
	      << "s and " << ressum.tv_nsec << "ns\n";
    std::cout << "DIFF: " << timespec_to_ms(resdiff) << "ms | "
	      << resdiff.tv_sec << "s and " << resdiff.tv_nsec << "ns\n";
    std::cout << "NOW: " << timespec_to_ms(now) << "ms | " << now.tv_sec
	      << "s and " << now.tv_nsec << "ns\n";
    std::cout << (time1_ts < time2_ts) << '\n';

    // Return
    return 0;
}
