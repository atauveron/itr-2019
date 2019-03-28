#include "PosixThread.h"

#include "timespec.h"

#include <cerrno>
#include <ctime>
#include <stdexcept>

volatile bool PosixThread::READY_ = false;
Mutex		  PosixThread::MUTEX_;

pthread_t PosixThread::INVALID_PTHREAD_ = 0;

void *PosixThread::dummyFunction(void *)
{
		Mutex::Lock l(PosixThread::MUTEX_);
		PosixThread::READY_ = true;
		l.notify();
		return nullptr;
}

pthread_t PosixThread::INVALID_PTHREAD()
{
		Mutex::Lock l(PosixThread::MUTEX_);

		if (INVALID_PTHREAD_ == 0)
		{
				pthread_create(&INVALID_PTHREAD_, nullptr, dummyFunction,
							   nullptr);
				while (!PosixThread::READY_)
				{
						l.wait();
						// HACK: make sure the dummy thread has finished
						timespec_wait(timespec_from_ms(10));
				}
		}

		return INVALID_PTHREAD_;
}

PosixThread::PosixThread()
{
		pthread_attr_init(&posixAttr);
		pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);

		posixId = INVALID_PTHREAD();

		// SCHED_OTHER by default
		pthread_attr_setschedpolicy(&posixAttr, SCHED_OTHER);
		sched_param schedParams;
		schedParams.sched_priority = 0;
		pthread_attr_setschedparam(&posixAttr, &schedParams);
}

PosixThread::PosixThread(pthread_t posixId) : posixId(posixId)
{
		pthread_attr_init(&posixAttr);
		pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);

		sched_param schedParams;
		int			policy;
		int retval = pthread_getschedparam(posixId, &policy, &schedParams);

		if (retval == ESRCH) { throw PosixThread::Exception(); }

		pthread_attr_setschedpolicy(&posixAttr, policy);
		pthread_attr_setschedparam(&posixAttr, &schedParams);
}

PosixThread::~PosixThread() { pthread_attr_destroy(&posixAttr); }

void PosixThread::start(void *(*threadFunc)(void *), void *threadArg)
{
		pthread_create(&posixId, &posixAttr, threadFunc, threadArg);
}

void PosixThread::join() { pthread_join(posixId, NULL); }

bool PosixThread::join(double timeout_ms)
{
		const timespec tspec(timespec_from_ms(timeout_ms));
		return !(bool)pthread_timedjoin_np(posixId, NULL, &tspec);
}

bool PosixThread::setScheduling(int schedPolicy, int priority)
{
		bool setPolicy =
			(bool)pthread_attr_setschedpolicy(&posixAttr, schedPolicy);
		sched_param schedParams;
		schedParams.sched_priority = priority;
		bool setSched =
			(bool)pthread_attr_setschedparam(&posixAttr, &schedParams);

		return !(setPolicy || setSched);
}

bool PosixThread::getScheduling(int *p_schedPolicy, int *p_priority) const
{
		sched_param schedParams;

		bool getPolicy =
			(bool)pthread_attr_getschedpolicy(&posixAttr, p_schedPolicy);

		bool getSched =
			(bool)pthread_attr_getschedparam(&posixAttr, &schedParams);

		*p_priority = schedParams.sched_priority;

		return !(getPolicy || getSched);
}

const char *PosixThread::Exception::what() const noexcept
{
		return "Process does not exist";
}