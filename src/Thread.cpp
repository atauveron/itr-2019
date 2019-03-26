#include "Thread.h"
#include "timespec.h"
#include <signal.h>

Thread::Thread() : chrono() {}

Thread::~Thread() {}

void Thread::start() { PosixThread::start(call_run, this); }

void *Thread::call_run(void *v_thread) {
    Thread *thread = reinterpret_cast<Thread *>(v_thread);
    thread->chrono.restart();
    thread->run();
    thread->chrono.stop();
}

void Thread::sleep_ms(double delay_ms) {
    timespec_wait(timespec_from_ms(delay_ms));
}

double Thread::startTime_ms() { return chrono.startTime(); }

double Thread::stopTime_ms() { return chrono.stopTime(); }

double Thread::execTime_ms() { return stopTime_ms() - startTime_ms(); }
