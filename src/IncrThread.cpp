/**
 * @file main_td2a.cpp
 * @brief Main file for tutorial question 2a
 */

// TODO UPDATE DOC

#include "IncrThread.h"

/**
 * @brief A function to increment a counter
 *
 * @param nLoops the number of loops to perform
 * @param[in,out] pCounter a pointer to the counter to increment
 */
IncrThread::IncrThread(volatile double *counter, unsigned int nLoops,
		       int sched_policy)
    : Thread(), p_counter(counter), loops(nLoops) {

    int sched_priority;
    if (sched_policy == SCHED_OTHER) {
	sched_priority = 0;
    } else {
	sched_priority = 9;
    }
    setScheduling(sched_policy, sched_priority);
}

IncrThread::IncrThread(IncrThread const &old) {
    p_counter = old.p_counter;
    loops = old.loops;
    int policy = 0;
    int priority = 0;

    old.getScheduling(&policy, &priority);
    setScheduling(policy, priority);
    start();
}

IncrThread::~IncrThread() {}

/**
 * @brief A function to increment a counter
 *
 * @param nLoops the number of loops to perform
 * @param[in,out] pCounter a pointer to the counter to increment
 */
void IncrThread::run() {
    for (unsigned int i(0); i < loops; ++i) {
	(*p_counter) += 1.0;
    }
    return;
}