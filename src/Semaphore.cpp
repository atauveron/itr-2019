#include "Semaphore.h"

Semaphore::Semaphore(
		unsigned int initCount = 0,
		unsigned int maxCount = std::numeric_limits<unsigned int>::max())
		: counter(initCount <= maxCount ? initCount : maxCount),
			maxCounter(maxCount), mtx() {}

void Semaphore::give() {
	Mutex::Lock lck(mtx);
	if (counter < maxCounter) {
		++counter;
	}
}

void Semaphore::take() {
	Mutex::Lock lck(mtx);
	while (counter == 0) {
		lck.wait();
	}
	--counter;
}

bool Semaphore::take(double timeout_ms) {
	Mutex::Lock lck(mtx);
	if (counter == 0) {
		lck.wait(timeout_ms);
	}
	if (counter > 0) {
		--counter;
		return true;
	} else {
		return false;
	}
}
