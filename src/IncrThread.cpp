#include "IncrThread.h"

IncrThread::IncrThread(volatile double *counter, unsigned int nLoops,
					   int sched_policy) :
	Thread(),
	p_counter(counter), loops(nLoops)
{

		int sched_priority = sched_policy == SCHED_OTHER ? 0 : 9;
		setScheduling(sched_policy, sched_priority);
}

IncrThread::IncrThread(IncrThread const &other)
{
		p_counter	= other.p_counter;
		loops		 = other.loops;
		int policy   = 0;
		int priority = 0;

		other.getScheduling(&policy, &priority);
		setScheduling(policy, priority);
}

IncrThread::~IncrThread() {}

void IncrThread::run()
{
		for (unsigned int i(0); i < loops; ++i) { (*p_counter) += 1.0; }
}