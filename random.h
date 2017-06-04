#pragma once

#include "types.h"
#include <ctime>

class Random
{
private:
	constexpr static uint32 c=1, a=1025;
	uint32 seed;
public:
	Random(uint32 seed)
	{
		this->seed=seed;
	}
	void Reset(uint32 seed)
	{
		this->seed=seed;
	}
	uint32 Next()
	{
		seed=(seed*a+c);
		return seed;
	}
	uint32 Next(uint32 range)
	{
		return Next()%range;
	}
	uint32 Next(uint32 min, uint32 max)
	{
		return min+Next(max-min+1);
	}
	double NextDouble(uint32 divisor=1'000'000'000)
	{
		return Next()+(Next()/double(divisor));
	}
	uint64 NextLong()
	{
		return (uint64(Next())<<32)+Next();
	}
	bool NextBool(uint8 probability=50)
	{
		return Next(100)<probability;
	}
};
Random random(time(nullptr));