/**
 * @file Timer.h
 * @brief Implementations of the Timer class
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
  void start(double duration_ms);
  void stop();

protected:
  virtual void callback() = delete;

private:
  static void call_callback(int sig, siginfo_t *si, void *user);
};

#endif