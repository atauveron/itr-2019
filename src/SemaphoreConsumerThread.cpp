#include "SemaphoreConsumerThread.h"

SemaphoreConsumerThread::SemaphoreConsumerThread(Semaphore *p_semaphore) :
	semaphore(p_semaphore), consumedTokens(0)
{
}

SemaphoreConsumerThread::SemaphoreConsumerThread(
	SemaphoreConsumerThread const &other) :
	semaphore(other.semaphore),
	consumedTokens(0)
{
}

SemaphoreConsumerThread::~SemaphoreConsumerThread() {}

void SemaphoreConsumerThread::run()
{
		while (semaphore->take(1000)) { ++consumedTokens; }
}

int SemaphoreConsumerThread::tokens() { return consumedTokens; }