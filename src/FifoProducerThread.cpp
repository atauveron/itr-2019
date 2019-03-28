#include "FifoProducerThread.h"

FifoProducerThread::FifoProducerThread(Fifo<int> *  p_fifo,
									   unsigned int nTokens) :
	fifo(p_fifo),
	producedTokens(0), targetTokens(nTokens)
{
}

FifoProducerThread::FifoProducerThread(FifoProducerThread const &other) :
	fifo(other.fifo), producedTokens(0), targetTokens(other.targetTokens)
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