/**
 * @file main_td1e.cpp
 * @brief Main file for tutorial question 1e
 * Most of the work for this question is in files `timespec.h` and
 * `timespec.cpp`.
 */
#include <ctime>
#include <iostream>

#include "timespec.h"

int main(int argc, char **argv) {
  timespec time1_ts{.tv_sec = 5, .tv_nsec = 0};
  timespec time2_ts{.tv_sec = 5, .tv_nsec = 500000000};
  timespec res = timespec_add(time1_ts, time2_ts);
  std::cout << res.tv_sec << "s, " << res.tv_nsec << "ns\n";
  std::cout << (time1_ts < time2_ts) << '\n';

  // Return
  return 0;
}
