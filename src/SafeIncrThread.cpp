#include "SafeIncrThread.h"

SafeIncrThread::SafeIncrThread(volatile double *counter, unsigned int nLoops,
							   int sched_policy, Mutex *mtx) :
	Thread(),
	p_counter(counter), loops(nLoops), mutex(mtx)
{

		int sched_priority = sched_policy == SCHED_OTHER ? 0 : 9;
		setScheduling(sched_policy, sched_priority);
}

SafeIncrThread::SafeIncrThread(SafeIncrThread const &other)
{
		int policy   = 0;
		int priority = 0;
		loops		 = other.loops;
		mutex		 = other.mutex;

		p_counter = other.p_counter;

		other.getScheduling(&policy, &priority);
		setScheduling(policy, priority);
}

SafeIncrThread::~SafeIncrThread() {}

void SafeIncrThread::run()
{
		for (unsigned int i(0); i < loops; ++i)
		{
				Mutex::Lock lock(*mutex);
				(*p_counter) += 1.0;
		}
}