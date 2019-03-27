#include "Calibrator.h"
#include "Chrono.h"
#include "CpuLoop.h"
#include <iostream>

int main() {
    Calibrator callibrator(1000, 2);
    CpuLoop loop(callibrator);

    Chrono chrono;
    loop.runTime(10000);
    chrono.stop();

    std::cout << chrono.lap() << std::endl;

    return 0;
}