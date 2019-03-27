#include "PosixThread.h"

#include <cerrno>
#include <ctime>
#include <stdexcept>

#include "timespec.h"

PosixThread::PosixThread() {
    pthread_attr_init(&posixAttr);
    pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);

    // SCHED_OTHER by default
    pthread_attr_setschedpolicy(&posixAttr, SCHED_OTHER);
    sched_param schedParams;
    schedParams.sched_priority = 0;
    pthread_attr_setschedparam(&posixAttr, &schedParams);
}

PosixThread::PosixThread(pthread_t posixId) : posixId(posixId) {
    pthread_attr_init(&posixAttr);
    pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);

    sched_param schedParams;
    int policy;

    int retval = pthread_getschedparam(posixId, &policy, &schedParams);

    if (retval == ESRCH) {
	throw PosixThread::Exception();
    }

    pthread_attr_setschedpolicy(&posixAttr, policy);
    pthread_attr_setschedparam(&posixAttr, &schedParams);
}

PosixThread::~PosixThread() {
    join();
    pthread_attr_destroy(&posixAttr);
}

void PosixThread::start(void *(*threadFunc)(void *), void *threadArg) {
    pthread_create(&posixId, &posixAttr, threadFunc, threadArg);
}

void PosixThread::join() { pthread_join(posixId, NULL); }

bool PosixThread::join(double timeout_ms) {
    const timespec tspec(timespec_from_ms(timeout_ms));
    return !(bool)pthread_timedjoin_np(posixId, NULL, &tspec);
}

bool PosixThread::setScheduling(int schedPolicy, int priority) {
    bool setPolicy = (bool)pthread_attr_setschedpolicy(&posixAttr, schedPolicy);
    sched_param schedParams;
    schedParams.sched_priority = priority;
    bool setSched = (bool)pthread_attr_setschedparam(&posixAttr, &schedParams);
    return !(setPolicy || setSched);
}

bool PosixThread::getScheduling(int *p_schedPolicy, int *p_priority) const {
    bool getPolicy =
	(bool)pthread_attr_getschedpolicy(&posixAttr, p_schedPolicy);
    sched_param schedParams;
    bool getSched = (bool)pthread_attr_getschedparam(&posixAttr, &schedParams);
    *p_priority = schedParams.sched_priority;
    return !(getPolicy || getSched);
}

const char *PosixThread::Exception::what() const noexcept {
    return "Process does not exist";
}