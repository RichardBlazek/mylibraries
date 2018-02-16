#pragma once

#include <chrono>

class StopWatch
{
private:
	using clock=std::chrono::steady_clock;
	clock::time_point last;
public:
	StopWatch():last(clock::now()){}
	void Reset()
	{
		last=clock::now();
	}
	clock::time_point StartTime()const
	{
		return last;
	}
	template<typename Rep, typename Period>
	auto ElapsedTime()const
	{
		return clock::now()-last;
	}
};

class LoopTime
{
private:
	StopWatch time;
public:
	LoopTime()=default;
	template<typename Rep, typename Period>
	void NextLoop(std::chrono::duration<Rep, Period> loop_time)
	{
		std::this_thread::sleep_until(time.StartTime()+loop_time);
		time.Reset()
	}
};