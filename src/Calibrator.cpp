#include "Calibrator.h"
#include <pthread.h>

Calibrator::Calibrator(double samplingPeriod_ms, unsigned int nSamples)
    : samples({}), counter(nSamples) {
    Looper localLooper{};
    looper = &localLooper;

    pthread_t posixId;

    pthread_create(&posixId, nullptr, looper->call_loop, looper);
    start(samplingPeriod_ms);
    pthread_join(posixId, NULL);

    looper = nullptr;

    double values[2];

    Calibrator::regressionError(values, samples, nSamples, samplingPeriod_ms);

    a = values[0];
    b = values[1];
}

void Calibrator::regressionError(double *values, std::vector<double> Y,
				 unsigned N, double dx) {
    double xMean = dx * (N + 1) / 2;
    double yMean = 0;
    double xyError = 0;
    double squareXError = 0;

    // Compute Mean
    for (unsigned int i = 0; i < N; ++i) {
	yMean += Y[i];
    }

    yMean /= N;

    // Compute Mean Square Error and XY Error to deduce slope
    for (unsigned int i = 0; i < N; ++i) {
	xyError += (xMean - (i + 1) * dx) * (yMean - Y[i]);
	squareXError += (xMean - (i + 1) * dx) * (xMean - (i + 1) * dx);
    }

    double slope = xyError / squareXError;
    double offset = yMean - slope * xMean;
    values[0] = slope;
    values[1] = offset;

    // Return
    return;
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
