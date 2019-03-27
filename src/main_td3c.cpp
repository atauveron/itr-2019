#include "Calibrator.h"
#include "Chrono.h"
#include "CpuLoop.h"
#include <iostream>

int main() {
    Calibrator callibrator(1000, 10);
    CpuLoop loop(callibrator);

    std::cout << "Running for 10 sec" << std::endl;
    Chrono chrono;
    loop.runTime(10000);
    chrono.stop();

    std::cout << "Result in ms: " << chrono.lap() << std::endl;

    return 0;
}