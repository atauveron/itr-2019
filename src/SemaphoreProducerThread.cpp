#include "SemaphoreProducerThread.h"

SemaphoreProducerThread::SemaphoreProducerThread(Semaphore *  p_semaphore,
												 unsigned int nTokens) :
	semaphore(p_semaphore), targetTokens(nTokens),
	producedTokens(0)
{
}

SemaphoreProducerThread::SemaphoreProducerThread(
	SemaphoreProducerThread const &other) :
	semaphore(other.semaphore),
	targetTokens(other.targetTokens),
	producedTokens(0)
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