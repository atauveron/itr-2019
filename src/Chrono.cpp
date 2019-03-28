#include "Chrono.h"

#include "timespec.h"

Chrono::Chrono() : startTime_(timespec_now()), stopTime_(startTime_) {}

void Chrono::stop() { stopTime_ = timespec_now(); }

void Chrono::restart()
{
		startTime_ = timespec_now();
		stopTime_  = startTime_;
}

bool Chrono::isActive() { return startTime_ == stopTime_; }

double Chrono::startTime() { return timespec_to_ms(startTime_); }

double Chrono::stopTime() { return timespec_to_ms(stopTime_); }

double Chrono::lap()
{
		timespec lap =
			isActive() ? timespec_now() - startTime_ : stopTime_ - startTime_;

		return timespec_to_ms(lap);
}
