#include "../GRenderer.h"
#include <chrono>

GGeneral::Time::Timer::Timer() {
	auto nano = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch());
	startTime = nano.count();
}

unsigned long long int GGeneral::Time::Timer::stop() const {
	auto nano = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch());
	return nano.count() - startTime;
}

const bool GGeneral::Time::isLeapYear(TimePoint& point) {
	auto year = point.year;
	return !(year % 4) && (year % 100) || !(year % 400);
}

const bool GGeneral::Time::isLeapYear(const unsigned int year) {
	return !(year % 4) && (year % 100) || !(year % 400);
}