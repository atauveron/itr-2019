#include "Countdown.h"
#include <iostream>
#include <unistd.h>

int main() {
    Countdown countdown(10);
    countdown.start(100);

    std::cout << "start" << std::endl;
    for (int i; i < 1000000; i++) {
        sleep(1000);
    }

    std::cout << "stop" << std::endl;

    return 0;
}