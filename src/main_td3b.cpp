#include "Countdown.h"
#include <iostream>
#include <unistd.h>

int main() {
    Countdown countdown(10);
    countdown.start(100);

    std::cout << "start" << std::endl;
    while (countdown.counter > -10) {
    }

    std::cout << "stop" << std::endl;

    return 0;
}