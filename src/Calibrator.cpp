#include "Calibrator.h"

#include "PosixThread.h"

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples)
		: samples({}) {
	Looper localLooper{};
	looper = &localLooper;
	PosixThread thread{};

	start(samplingPeriod_ms);
	thread.start(looper->runLoops, nullptr);
	while (samples.size() < nSamples) {
		// Wait for enough samples
	}
	stop();
	looper->stopLoop();
	looper = nullptr;
	thread.join();

	a = (samples[1] - samples[0]) / samplingPeriod_ms;
	b = (samples[1] + samples[0]) - a * (3 * samplingPeriod_ms);
	b /= 2;
}

double Calibrator::nLoops(double duration_ms) { return a * duration_ms + b; }

void Calibrator::callback() { samples.push_back(looper->getSamples()); }
