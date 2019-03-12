#include "Countdown.h"

#include <unistd.h>

int main(int argc, char **argv) {
	Countdown countdown(10);
	countdown.start(1000);

	sleep(20000);

	return 0;
}