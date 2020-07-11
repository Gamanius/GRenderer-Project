#include "../GRenderer.h"
#include <chrono>

#pragma warning(disable : 4244)
constexpr unsigned long long int nanoToDay = 8.64e13;
constexpr unsigned long long int nanoToHour = 3.6e12;
constexpr unsigned long long int nanoToMinute = 6e10;
constexpr unsigned long long int nanoToSecond = 1e9;
constexpr unsigned long long int nanoToMillieSecond = 1e6;
constexpr unsigned long long int nanoToMicroSecond = 1e3;

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

GGeneral::Time::TimePoint GGeneral::Time::getCurrentTime() {
	auto nano = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch());
	TimePoint p;
	p.timepoint = nano.count();
	return fillTimePoint(p);
}

unsigned long long GGeneral::Time::getNanoTime() {
	return std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch()).count();
}

unsigned int GGeneral::Time::daysToYears(unsigned int day) {
	unsigned int i = 0;
	while (yearsToDays(i) < day)
		i++;
	return --i;
}

unsigned int GGeneral::Time::yearsToDays(unsigned int year) {
	unsigned int days = 0;
	for (unsigned int i = 0; i < year; i++) {
		days += GGeneral::Time::isLeapYear(i + 1970) ? 366 : 365;
	}
	return days;
}

unsigned int GGeneral::Time::monthsToDays(byte m) {
	return monthsToDays(m, false);
}

unsigned int GGeneral::Time::monthsToDays(byte m, bool leap) {
	unsigned short days = 0;
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

byte GGeneral::Time::daysToMonths(unsigned short d) {
	return daysToMonths(d, false);
}

byte GGeneral::Time::daysToMonths(unsigned short d, bool leap) {
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