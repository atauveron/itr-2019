#include "Thread.h"
#include "timespec.h"
#include <signal.h>

Thread::Thread() : chrono() {}

Thread::~Thread() {}

void Thread::start() { call_run(this); }

// DOES NOT USE A THREAD !!!!
void *Thread::call_run(void *v_thread) {
  Thread *thread = reinterpret_cast<Thread *>(v_thread);
  thread->chrono.restart();
  thread->run();
  thread->join(); /// NOTHING TO JOIN
  thread->chrono.stop;
}

void sleep_ms(double delay_ms) { timespec_wait(timespec_from_ms(delay_ms)); }

double Thread::startTime_ms() { return chrono.startTime(); }

double Thread::stopTime_ms() { return chrono.stopTime(); }

double Thread::execTime_ms() { return stopTime_ms() - startTime_ms(); }
