#include "CpuLoop.h"

CpuLoop::CpuLoop(Calibrator &calibrator_) : calibrator(calibrator_) {}

void CpuLoop::runTime(double duration_ms) {
	double nLoops = calibrator.nLoops(duration_ms);
	runLoops(nLoops);
}
