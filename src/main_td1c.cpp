#include <climits>
#include <csignal>
#include <ctime>
#include <iostream>
#include <string>

#include "timespec.h"

struct stopData {
  volatile bool stop;
};

void handler(int sig, siginfo_t *si, void *) {
  stopData *stop = reinterpret_cast<stopData *>(si->si_value.sival_ptr);
  stop->stop = true;
  return;
}

unsigned incr(unsigned int nLoops, double *pCounter, volatile bool *pStop) {
  unsigned int i;
  for (i = 0; i < nLoops; ++i) {
    if (*pStop) {
      break;
    }
    (*pCounter) += 1.0;
  }
  return i;
}

unsigned int run(long int delay_s) {
  unsigned int nLoops(UINT_MAX);
  double counter(0);
  stopData stop{false};

  // Timer
  struct sigaction sa;
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = handler;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGRTMIN, &sa, nullptr);

  struct sigevent sev;
  sev.sigev_notify = SIGEV_SIGNAL;
  sev.sigev_signo = SIGRTMIN;
  sev.sigev_value.sival_ptr = &stop;

  timer_t tid;
  timer_create(CLOCK_REALTIME, &sev, &tid);
  itimerspec its;
  its.it_value = {delay_s, 0};
  its.it_interval = {0, 0};
  timer_settime(tid, 0, &its, nullptr);

  // Increment
  timespec start_ts, end_ts{};
  clock_gettime(CLOCK_REALTIME, &start_ts);
  nLoops = incr(nLoops, &counter, &stop.stop);
  clock_gettime(CLOCK_REALTIME, &end_ts);

  // DEBUG
  std::cout << "Execution time: " << timespec_to_ms(end_ts - start_ts)
            << "ms (requested " << delay_s << "s)\n";
  std::cout << "Number of loops: " << nLoops << '\n';
  // Delete timer
  timer_delete(tid);

  // Return
  return nLoops;
}

int main(int argc, char **argv) {

  // Run for 4 then 6 seconds
  unsigned int nLoops4 = run(4);
  unsigned int nLoops6 = run(6);

  // Output
  long int slope = (nLoops6 - nLoops4) / 2;
  long int offset = (long int)nLoops4 - 4 * slope;
  std::cout << "l(t)= " << slope << " * t + " << offset << '\n';

  // Return
  return 0;
}
