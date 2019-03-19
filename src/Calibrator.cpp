#include "Calibrator.h"

#include "PosixThread.h"

Calibrator::Calibrator(double samplingPeriod_ms, unsigned int nSamples)
		: samples({}), counter(nSamples) {
	Looper localLooper{};
	looper = &localLooper;
	PosixThread thread{};

	thread.start(looper->runLoops, nullptr);
	start(samplingPeriod_ms);
	thread.join();

	looper = nullptr;

	long int* values = regressionError(samples, nSamples, samplingPeriod_ms);
	// TODO Generalize to nSamples > 2
	// TODO Create a private method to compute
	a = values[0];
	b = values[1];
}

long int* regressionError(std::vector<double> Y, unsigned N, double dx)
{
	long int xMean = dx*(N+1)/2;
	long int yMean = 0;
	long int xyError = 0;
	long int squareXError = 0;

	long int values[2];

	// Compute Mean
	for (int i = 0; i < N ; ++i) {
		yMean += Y[i];
	}

	yMean /= N;

	// Compute Mean Square Error and XY Error to deduce slope
	for (int i = 0; i < N ; ++i) {
		xyError += (xMean - (i+1)*dx) * (yMean - Y[i]);
		squareXError += (xMean - (i+1)*dx) * (xMean - (i+1)*dx);
	}

	long int slope = xyError / squareXError;
	long int offset = yMean - slope * xMean;
	values[0] = slope;
	values[1] = offset;

	// Return
	return values;
}

double Calibrator::nLoops(double duration_ms) { return a * duration_ms + b; }

void Calibrator::callback() {
	--counter;

	if (counter == 0) {
		samples.push_back(looper->stopLoop());
		stop();
	} else {
		samples.push_back(looper->getSamples());
	}
}
