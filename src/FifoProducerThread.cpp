#include "FifoProducerThread.h"

FifoProducerThread::FifoProducerThread(Fifo<int> *  p_fifo,
									   unsigned int nTokens) :
	fifo(p_fifo), targetTokens(nTokens),
	producedTokens(0)
{
}

FifoProducerThread::FifoProducerThread(FifoProducerThread const &other) :
	fifo(other.fifo), targetTokens(other.targetTokens), producedTokens(0)
{
}

FifoProducerThread::~FifoProducerThread() {}

void FifoProducerThread::run()
{
		for (unsigned int k = 0; k < targetTokens; ++k)
		{
				fifo->push(k);
				++producedTokens;
		}
}

int FifoProducerThread::tokens() { return producedTokens; }