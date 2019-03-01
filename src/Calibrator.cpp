#include "Calibrator.h"

#include "PosixThread.h"

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples)
		: samples({}), counter(nSamples) {
	Looper localLooper{};
	looper = &localLooper;
	PosixThread thread{};

	thread.start(looper->runLoops, NULL);
	start(samplingPeriod_ms);
	thread.join();
	
	looper = nullptr;

	// TODO Generalize to nSamples > 2
	// TODO Create a private method to compute
	a = (samples[1] - samples[0]) / samplingPeriod_ms;
	b = (samples[1] + samples[0]) - a * (3 * samplingPeriod_ms);
	b /= 2;
}

double Calibrator::nLoops(double duration_ms) { return a * duration_ms + b; }

void Calibrator::callback() { 
	--counter;

	if (counter==0) {
		samples.push_back(looper->stopLoop());
		stop();
	} else {
		samples.push_back(looper->getSamples());
	}
}
