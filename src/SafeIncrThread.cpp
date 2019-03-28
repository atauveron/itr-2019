#include "SafeIncrThread.h"

SafeIncrThread::SafeIncrThread(volatile double *counter, unsigned int nLoops,
							   int sched_policy, Mutex *mtx)
	: Thread(), p_counter(counter), loops(nLoops), mutex(mtx) {

  int sched_priority;
  if (sched_policy == SCHED_OTHER) {
	sched_priority = 0;
  } else {
	sched_priority = 9;
  }
  setScheduling(sched_policy, sched_priority);
}

SafeIncrThread::SafeIncrThread(SafeIncrThread const &old) {
  p_counter = old.p_counter;
  loops = old.loops;
  mutex = old.mutex;
  int policy = 0;
  int priority = 0;

  old.getScheduling(&policy, &priority);
  setScheduling(policy, priority);
}

SafeIncrThread::~SafeIncrThread() {}

void SafeIncrThread::run() {
  for (unsigned int i(0); i < loops; ++i) {
	Mutex::Lock lock(*mutex);
	(*p_counter) += 1.0;
  }
  return;
}