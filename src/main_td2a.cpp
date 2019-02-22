#include <ctime>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>

#include "timespec.h"

struct Data {
  volatile unsigned int nLoops;
  volatile double *pCounter;
};

void incr(unsigned int nLoops, volatile double *pCounter) {
  for (unsigned int i(0); i < nLoops; ++i) {
    (*pCounter) += 1.0;
  }
  return;
}

void *call_incr(void *v_data) {
  Data *p_data = reinterpret_cast<Data *>(v_data);
  incr(p_data->nLoops, p_data->pCounter);
  return v_data;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <nLoops> <nTasks>\n";
    return 1;
  }
  unsigned int nLoops = std::stoul(argv[1]);
  unsigned int nTasks = std::stoul(argv[2]);
  double counter(0);

  // Thread
  Data data{nLoops, &counter};
  std::vector<pthread_t> incrementThreads(nTasks);

  // Time
  timespec start_ts, end_ts{};
  clock_gettime(CLOCK_REALTIME, &start_ts);
  for (auto &thread : incrementThreads) {
    pthread_create(&thread, nullptr, call_incr, &data);
  }
  for (auto &thread : incrementThreads) {
    pthread_join(thread, nullptr);
  }
  clock_gettime(CLOCK_REALTIME, &end_ts);
  std::cout << "Execution time: " << timespec_to_ms(end_ts - start_ts) / 1000
            << "s\n";
  std::cout << "Counter: " << counter << '\n';

  // Return
  return 0;
}
