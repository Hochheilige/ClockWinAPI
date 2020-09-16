#pragma once

#include <cstdint>
#include <ctime>
#include <iostream>
#include <iomanip>

#include <Windows.h>

class Time {
public:
	Time() : hours(0), minutes(0), seconds(0) {}
	Time(const uint8_t hrs, const uint8_t min, const uint8_t sec)
		: hours(hrs), minutes(min), seconds(sec) {}
	Time(const tm* const now_time)
		: hours(now_time->tm_hour), 
		  minutes(now_time->tm_min), 
		  seconds(now_time->tm_sec) {}

	inline bool IsSecondsLimit() const { return seconds == 60; }
	inline bool IsMinutesLimit() const { return minutes == 60; }
	inline bool IsHoursLimit() const { return hours == 24; }

	void Increase();
	void PrintCurrentTimeStd() const;
	void PrintCurrentTimeWnd() const;
	Time CurrentTime() const;
private:
	uint8_t hours, minutes, seconds;
};