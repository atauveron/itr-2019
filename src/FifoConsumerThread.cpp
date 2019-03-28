#include "FifoConsumerThread.h"

FifoConsumerThread::FifoConsumerThread(Fifo<int> *p_fifo, Mutex *mtx) :
	fifo(p_fifo), mutex(mtx), consumedTokens(0)
{
}

FifoConsumerThread::FifoConsumerThread(FifoConsumerThread const &other) :
	fifo(other.fifo), consumedTokens(0)
{
}

FifoConsumerThread::~FifoConsumerThread() {}

void FifoConsumerThread::run()
{
		bool active(true);
		while (active)
		{
				try
				{
						int			tmp = fifo->pop(1000); // 1 second timeout
						Mutex::Lock lck(*mutex);
						consumedTokens++;
				}
				catch (const Fifo<int>::EmptyException &e)
				{
						active = false;
				}
		}
}

int FifoConsumerThread::tokens() { return consumedTokens; }