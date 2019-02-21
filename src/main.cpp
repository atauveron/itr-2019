#include <csignal>
#include <ctime>
#include <iostream>

#include "timespec.h"

void handler(int sig, siginfo_t *si, void *) {
  std::cout << "Handler called\n";
  return;
}

#if 0
void call_timer() {
  int counter(0);

  struct sigaction sa;
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = handler;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGRTMIN, &sa, nullptr);

  struct sigevent sev;
  sev.sigev_notify = SIGEV_SIGNAL;
  sev.sigev_signo = SIGRTMIN;
  sev.sigev_value.sival_ptr = &counter;

  timer_t tid;
  timer_create(CLOCK_REALTIME, &sev, &tid);
  itimerspec its;
  its.it_value = {0, 0};
  its.it_interval = {0, 500000000};
  timer_settime(tid, 0, &its, nullptr);
  // TODO
  timer_delete(tid);
}
#endif

int main(int argc, char **argv) {
  std::cout << "Hello world !\n";
  timespec time1_ts{.tv_sec = 5, .tv_nsec = 0};
  timespec time2_ts{.tv_sec = 5, .tv_nsec = 500000000};
  timespec res = timespec_add(time1_ts, time2_ts);
  std::cout << res.tv_sec << "s, " << res.tv_nsec << "ns\n";
  std::cout << (time1_ts < time2_ts) << '\n';
  return 0;
}
