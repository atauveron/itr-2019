#include "SemaphoreProducerThread.h"

SemaphoreProducerThread::SemaphoreProducerThread(Semaphore *  p_semaphore,
												 unsigned int nTokens) :
	semaphore(p_semaphore),
	producedTokens(0), targetTokens(nTokens)
{
}

SemaphoreProducerThread::SemaphoreProducerThread(
	SemaphoreProducerThread const &other) :
	semaphore(other.semaphore),
	producedTokens(0), targetTokens(other.targetTokens)
{
}

SemaphoreProducerThread::~SemaphoreProducerThread() {}

void SemaphoreProducerThread::run()
{
		for (unsigned int k = 0; k < targetTokens; ++k)
		{
				semaphore->give();
				++producedTokens;
		}
}

int SemaphoreProducerThread::tokens() { return producedTokens; }