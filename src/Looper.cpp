#include "Looper.h"

double Looper::runLoops(double nLoops) {
	doStop = false;
	for (auto k = 0; k < nLoops; ++k) {
		++iLoop;
		if (doStop) {
			break;
		}
	}
	return iLoop;
}

void* Looper::call_loop(void* v_data) {
	Looper* loop = reinterpret_cast<Looper *>(v_data);
	loop->runLoops();
}

double Looper::getSamples() { return iLoop; }

double Looper::stopLoop() {
	doStop = true;
	return iLoop;
}
