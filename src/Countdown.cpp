#include "Countdown.h"
#include "PeriodicTimer.h"

Countdown::Countdown(int n) : PeriodicTimer() {
	counter = n;
}

void Countdown::callback() {
	--counter;

	if (counter == 0) {
		this->stop();
	}
}