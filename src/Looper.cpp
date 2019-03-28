#include "Looper.h"

double Looper::runLoops(double nLoops)
{
		doStop = false;
		iLoop  = 0;
		for (auto k = 0; k < nLoops; ++k)
		{
				++iLoop;
				if (doStop) { break; }
		}

		return iLoop;
}

void *Looper::call_loop(void *v_data)
{
		Looper *loop = reinterpret_cast<Looper *>(v_data);
		loop->runLoops();

		return nullptr;
}

double Looper::getSamples() { return iLoop; }

double Looper::stopLoop()
{
		doStop = true;
		return iLoop;
}
