#include "Countdown.h"
#include <iostream>

Countdown::Countdown(int n) : counter(n) {}

void Countdown::callback() {
	--counter;

	std::cout << counter << std::endl;

	if (counter == 0) {
		stop();
		std::cout << "counter stopped" << std::endl;
	}
}