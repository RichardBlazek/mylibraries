#pragma once

#include <iostream>
#include <stdexcept>
#include <ctime>

#include "types.h"

namespace time
{
using std::clock_t;
using std::time_t;
constexpr uint32 MinutesInDay=24*60;
constexpr uint32 SecondsInDay=24*60*60;
constexpr clock_t ClocksPerSec=CLOCKS_PER_SEC;

inline bool IsLeapYear(uint16 year)noexcept
{
	return (year%4==0)&&(year%100!=0||year%400==0);
}
inline uint16 DaysInYear(uint16 year)noexcept
{
	return IsLeapYear(year)?366:365;
}
uint8 DaysInMonth(uint16 year, uint8 month)noexcept
{
	if(month==2)return IsLeapYear(year)?29:28;
	if(month<8)	return (month%2==0)?30:31;
	else		return (month%2==0)?31:30;
}

class Duration
{
private:
	time_t time=0;
public:
    Duration()=default
    Duration(time_t time):time(time){}
    inline time_t InSeconds()const noexcept
    {
    	return time;
    }
    inline uint16 Seconds()
    {
    	return InSeconds()%60;
    }
    inline time_t InMinutes()const noexcept
    {
    	return time/60;
    }
    inline uint16 Minutes()
    {
    	return InMinutes()%60;
    }
    inline time_t InHours()const noexcept
    {
    	return time/3600;
    }
    inline uint16 Hours()
    {
    	return InHours()%24;
    }
    inline uint32 InDays()const noexcept
    {
    	return time/86400;
    }
    inline uint32 Days()const noexcept
    {
    	return InDays();
    }
    inline Duration operator+(Duration d2)const noexcept
    {
    	return Duration(time+d2.time);
    }
    inline Duration operator-(Duration d2)const noexcept
    {
    	return Duration(time-d2.time);
    }
    inline bool operator==(Duration d2)const noexcept
    {
		return time==d2.time;
    }
    inline bool operator!=(Duration d2)const noexcept
    {
		return time!=d2.time;
    }
    inline bool operator<(Duration d2)const noexcept
    {
		return time<d2.time;
    }
    inline bool operator>(Duration d2)const noexcept
    {
		return time>d2.time;
    }
    inline bool operator<=(Duration d2)const noexcept
    {
		return time<=d2.time;
    }
    inline bool operator>=(Duration d2)const noexcept
    {
		return time>=d2.time;
    }
};

class Clock
{
private:
	clock_t time;
public:
	Clock()noexcept:time(0){}
	Clock(clock_t clc)noexcept:time(clc){}
	Clock(const Clock& clc)noexcept:time(clc.time){}
	static Clock Now()noexcept
	{
		return Clock(clock());
	}
	Clock operator-(Clock clc)const noexcept
	{
		return Clock(time-clc.time);
	}
	Clock operator+(Clock clc)const noexcept
	{
		return Clock(time+clc.time);
	}
	inline bool operator<(Clock tm2)const noexcept
	{
		return time<tm2.time;
	}
	inline bool operator>(Clock tm2)const noexcept
	{
		return time>tm2.time;
	}
	inline bool operator==(Clock tm2)const noexcept
	{
		return time==tm2.time;
	}
	inline bool operator<=(Clock tm2)const noexcept
	{
		return time<=tm2.time;
	}
	inline bool operator>=(Clock tm2)const noexcept
	{
		return time>=tm2.time;
	}
	inline bool operator!=(Clock tm2)const noexcept
	{
		return time!=tm2.time;
	}
};

class Time
{
private:
	time_t time=0;
public:
	enum class DayInWeek:uint8
	{
		Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday
	};
	Time()noexcept{}
	explicit Time(uint16 year, uint8 month=1, uint8 day=1, uint8 hour=0, uint8 minute=0, uint8 second=0, bool isDaylightSavingTime=false)
	{
        tm tmp={second, minute, hour, day, month, (year<1900)?0:year-1900, 1,1, isDaylightSavingTime};
        time=mktime(&tmp);
	}
	static Time Now()noexcept
	{
        Time tim;
        time::time(&tim.time);
        return tim;
	}
	Duration TimeOnly()const noexcept
	{
        return Duration(time%86400);
	}
	Time DateOnly()const noexcept
	{
		return Time(time-time%86400);
	}
	static Time Today()noexcept
	{
		return Now().DateOnly();
	}
	explicit operator std::string()const noexcept
	{
        return std::string(asctime(localtime(&time)));
	}
	friend std::ostream& operator<<(std::ostream& out, Time tim)
	{
		return out<<std::string(tim);
	}
	std::string FmtAsString(std::string Format, std::size_t MaxSize=128)const
	{
		char* c_string=new char[MaxSize];
		strftime(c_string, MaxSize, Format.c_str(), localtime(&time));
		std::string res=c_string;
		delete c_string;
		return res;
	}
	Duration operator-(Time tm2)const noexcept
	{
		return Duration(difftime(time, tm2.time));
	}
	Time operator+(Duration tm2)const noexcept
	{
		return Time(time+tm2.InSeconds());
	}
	Time operator-(Duration tm2)const noexcept
	{
		return Time(time-tm2.InSeconds());
	}
	Time AddSeconds(time_t tm2)const noexcept
	{
		return Time(time+tm2);
	}
	Time AddMinutes(time_t tm2)const noexcept
	{
		return Time(time+tm2*60);
	}
	Time AddHours(uint32 tm2)const noexcept
	{
		return Time(time+tm2*3600);
	}
	Time AddDays(uint16 tm2)const noexcept
	{
		return Time(time+tm2*86400);
	}
	Time AddWeeks(uint16 tm2)const noexcept
	{
		return Time(time+tm2*86400*7);
	}
	void SetDay(uint8 day)
	{
		tm tmp;
		tmp=*localtime(&time);
		if(day>DaysInMonth(tmp.tm_year,tmp.tm_mon)||day<1)
		{
			throw std::logic_error("Time::SetDay>This month has not so much days");
		}
		tmp.tm_mday=day;
		time=mktime(&tmp);
	}
	void SetMonth(uint8 mon)
	{
		if(mon>12||mon<1)
		{
			throw std::logic_error("Time::SetMonth>This month does not exist");
		}
		tm tmp;
		tmp=*localtime(&time);
		tmp.tm_mon=mon-1;
		time=mktime(&tmp);
	}
	void SetYear(uint16 year)
	{
		if(year<1900)
		{
			throw std::logic_error("Time::SetYear>This class can handle only years since 1900");
		}
		tm tmp;
		tmp=*localtime(&time);
		tmp.tm_year=year-1900;
		time=mktime(&tmp);
	}
	inline bool operator<(Time tm2)const noexcept
	{
		return time<tm2.time;
	}
	inline bool operator>(Time tm2)const noexcept
	{
		return time>tm2.time;
	}
	inline bool operator==(Time tm2)const noexcept
	{
		return time==tm2.time;
	}
	inline bool operator<=(Time tm2)const noexcept
	{
		return time<=tm2.time;
	}
	inline bool operator>=(Time tm2)const noexcept
	{
		return time>=tm2.time;
	}
	inline bool operator!=(Time tm2)const noexcept
	{
		return time!=tm2.time;
	}
	inline uint16 Year()const noexcept
	{
		return localtime(&time)->tm_year+1900;
	}
	inline uint16 Month()const noexcept
	{
		return localtime(&time)->tm_mon;
	}
	inline uint16 Day()const noexcept
	{
		return localtime(&time)->tm_mday;
	}
	inline uint16 DayInYear()const noexcept
	{
		return localtime(&time)->tm_yday;
	}
	inline DayInWeek WeekDay()const noexcept
	{
		return DayInWeek(localtime(&time)->tm_wday);
	}
	inline uint16 Hour()const noexcept
	{
		return time/3600%24;
	}
	inline uint16 Minute()const noexcept
	{
		return time/60%60;
	}
	inline uint16 Second()const noexcept
	{
		return time%60;
	}
	inline bool IsDaylightSavingTime()const noexcept
	{
		return (localtime(&time)->tm_isdst>0);
	}
};
}