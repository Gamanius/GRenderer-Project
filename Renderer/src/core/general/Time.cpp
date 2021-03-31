#include "GRenderer.h"
#include <chrono>

#pragma warning(disable : 4244)
constexpr uint64_t nanoToDay = 8.64e13;
constexpr uint64_t nanoToHour = 3.6e12;
constexpr uint64_t nanoToMinute = 6e10;
constexpr uint64_t nanoToSecond = 1e9;
constexpr uint64_t nanoToMillieSecond = 1e6;
constexpr uint64_t nanoToMicroSecond = 1e3;

GGeneral::Time::Timer::Timer() {
	auto nano = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch());
	startTime = nano.count();
}

uint64_t GGeneral::Time::Timer::stop() const {
	auto nano = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch());
	return nano.count() - startTime;
}

const bool GGeneral::Time::isLeapYear(const TimePoint& point) {
	auto year = point.year;
	return !(year % 4) && (year % 100) || !(year % 400);
}

const bool GGeneral::Time::isLeapYear(const uint32_t year) {
	return !(year % 4) && (year % 100) || !(year % 400);
}

GGeneral::Time::TimePoint GGeneral::Time::getCurrentTime() {
	auto nano = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch());
	TimePoint p;
	p.timepoint = nano.count();
	return fillTimePoint(p);
}

uint64_t GGeneral::Time::getNanoTime() {
	return std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch()).count();
}

uint32_t GGeneral::Time::daysToYears(uint32_t day) {
	uint32_t i = 0;
	while (yearsToDays(i) < day)
		i++;
	return --i;
}

uint32_t GGeneral::Time::yearsToDays(uint32_t year) {
	uint32_t days = 0;
	for (uint32_t i = 0; i < year; i++) {
		days += GGeneral::Time::isLeapYear(i + 1970) ? 366 : 365;
	}
	return days;
}

uint32_t GGeneral::Time::monthsToDays(byte m) {
	return monthsToDays(m, false);
}

uint32_t GGeneral::Time::monthsToDays(byte m, bool leap) {
	uint16_t days = 0;
	for (size_t i = 1; i < m; i++) {
		if (i == 2)
			if (leap)
				days += 29; //Leap year
			else
				days += 28; //Common year
		else if (i % 2 == 0)
			days += 30; //Even month hast 30 days
		else
			days += 31; //All other months
	}
	return days;
}

byte GGeneral::Time::daysToMonths(uint16_t d) {
	return daysToMonths(d, false);
}

byte GGeneral::Time::daysToMonths(uint16_t d, bool leap) {
	for (byte i = 1; i < 13; i++) {
		byte next;
		if (i == 2)
			if (leap)
				next = 29; //Leap year
			else
				next = 28; //Common year
		else if (i % 2 == 0)
			next = 30; //Even month hast 30 days
		else
			next = 31; //All other months
		if (d < next)
			return i;
		else
			d -= next;
	}
	return 12;
}

GGeneral::Time::TimePoint& GGeneral::Time::fillTimePoint(TimePoint& t) {
	auto remainder = t.timepoint;
	t.day = remainder / nanoToDay;

	remainder -= t.day * nanoToDay;
	t.hour = remainder / nanoToHour;

	remainder -= t.hour * nanoToHour;
	t.minute = remainder / nanoToMinute;

	remainder -= t.minute * nanoToMinute;
	t.seconds = remainder / nanoToSecond;

	remainder -= t.seconds * nanoToSecond;
	t.millisecond = remainder / nanoToMillieSecond;

	remainder -= t.millisecond * nanoToMillieSecond;
	t.microsecond = remainder / nanoToMicroSecond;

	remainder -= t.microsecond * nanoToMicroSecond;
	t.nanosecond = remainder;
	if (t.day >= 356) {
		t.year = daysToYears(t.day/*, t.timepoint / 3.16224e16*/);
		t.day -= yearsToDays(t.year);
	}
	t.month = daysToMonths(t.day, isLeapYear(t.year));
	t.day -= monthsToDays(t.month);

	return t;
}