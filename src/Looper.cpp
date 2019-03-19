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

double Looper::runLoops() {
	Looper::runLoops(std::numeric_limits<double>::max());
}

double Looper::getSamples() { return iLoop; }

double Looper::stopLoop() {
	doStop = true;
	return iLoop;
}
