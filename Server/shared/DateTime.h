#pragma once

#include <ctime>

class DateTime
{
public:
	// Uses the current time by default
	DateTime()
	{
		time_t now;
		time(&now);
		_tm = localtime(&now);
	}

	// Uses the timestamp specified
	DateTime(time_t timestamp)
	{
		_tm = localtime(&timestamp);
	}

	// Constructs a date/time using the specified date parts.
	DateTime(uint16_t sYear, uint8_t bMonth, uint8_t bDay, uint8_t bHour = 0, uint8_t bMinute = 0, uint8_t bSecond = 0)
	{
		// Get the current time
		time_t now;
		time(&now);
		_tm = localtime(&now);

		// Now update it with the data specified
		_tm->tm_year = sYear - 1900;
		_tm->tm_mon = bMonth - 1;
		_tm->tm_mday = bDay;
		_tm->tm_hour = bHour;
		_tm->tm_min = bMinute;
		_tm->tm_sec = bSecond;

		// Finally reconstruct it, so the other data is updated.
		Update();
	}

	// Uses the specified time struct
	DateTime(struct tm * _tm)
	{
		this->_tm = _tm;
	}

	// Simple getters to retrieve & convert time data to a more conventional form
	uint16_t GetYear() { return _tm->tm_year + 1900; }
	uint8_t GetMonth() { return _tm->tm_mon + 1; }
	uint8_t GetDay() { return _tm->tm_mday; }
	uint8_t GetDayOfWeek() { return _tm->tm_wday; }
	uint8_t GetHour() { return _tm->tm_hour; }
	uint8_t GetMinute() { return _tm->tm_min; }
	uint8_t GetSecond() { return _tm->tm_sec; }

	// NOTE: If any of these overflow, they'll be handled by mktime() accordingly.
	// This makes our life *much* easier; date/time logic is not pretty.

	void INLINE AddYears(int iYears)
	{
		_tm->tm_year += iYears;
		Update();
	}

	void INLINE AddMonths(int iMonths)
	{
		_tm->tm_mon += iMonths;
		Update();
	}

	void INLINE AddWeeks(int iWeeks)
	{
		AddDays(iWeeks * 7);
	}

	void INLINE AddDays(int iDays)
	{
		_tm->tm_mday += iDays;
		Update();
	}

	void INLINE AddHours(int iHours)
	{
		_tm->tm_hour += iHours;
		Update();
	}

	void INLINE AddMinutes(int iMinutes)
	{
		_tm->tm_min += iMinutes;
		Update();
	}

	void INLINE AddSeconds(int iSeconds)
	{
		_tm->tm_sec += iSeconds;
		Update();
	}

private:
	void INLINE Update() { mktime(_tm); }

protected:
	struct tm * _tm;
};