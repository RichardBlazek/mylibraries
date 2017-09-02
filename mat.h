#pragma once

#include "types.h"

namespace math
{
constexpr double pi=3.141592653589793;
double DegToRad(double deg)noexcept
{
	return deg*pi/180;
}
double RadToDeg(double rad)noexcept
{
	return rad*180/pi;
}
template<typename T>
T Abs(T val)noexcept
{
	return (val>0)?val:-val;
}
template<typename number, typename integral>
number RoundDown(number value, number unit)
{
    return integral(value/unit)*unit;
}
template<typename Float>
int64 Round(Float x)noexcept
{
	return int64(x)+(x-int64(x)>=0.5);
}
template<typename Float>
int64 RoundUp(Float x)noexcept
{
	return int64(x)+(x-int64(x)>0.0);
}
double Power(double x, int32 exp=2)noexcept
{
	if(exp<0)
	{
		return 1/Power(x, -exp);
	}
	else if(exp==0)
	{
		return 1;
	}
	double y=x;
	for(int32 i=1; i<exp; ++i)
	{
		x*=y;
	}
	return x;
}
double Root(double x, int32 a=2)noexcept
{
	double y=0;
	if(x<0&&(a&1)==0)
	{
		return 0;
	}
	while(Power(y+1e1, a)<=x)
	{
		y+=1e1;
	}
	while(Power(y+1e0, a)<=x)
	{
		y+=1e0;
	}
	while(Power(y+1e-1, a)<=x)
	{
		y+=1e-1;
	}
	while(Power(y+1e-2, a)<=x)
	{
		y+=1e-2;
	}
	while(Power(y+1e-3, a)<=x)
	{
		y+=1e-3;
	}
	while(Power(y+1e-4, a)<=x)
	{
		y+=1e-4;
	}
	while(Power(y+1e-5, a)<=x)
	{
		y+=1e-5;
	}
	while(Power(y+1e-6, a)<=x)
	{
		y+=1e-6;
	}
	while(Power(y+1e-7, a)<=x)
	{
		y+=1e-7;
	}
	while(Power(y+1e-8, a)<=x)
	{
		y+=1e-8;
	}
	while(Power(y+1e-9, a)<=x)
	{
		y+=1e-9;
	}
	while(Power(y+1e-10, a)<=x)
	{
		y+=1e-10;
	}
	while(Power(y+1e-11, a)<=x)
	{
		y+=1e-11;
	}
	while(Power(y+1e-12, a)<=x)
	{
		y+=1e-12;
	}
	while(Power(y+1e-13, a)<=x)
	{
		y+=1e-13;
	}
	while(Power(y+1e-14, a)<=x)
	{
		y+=1e-14;
	}
	while(Power(y+1e-15, a)<=x)
	{
		y+=1e-15;
	}
	return y;
}
uint64 Fact(uint8 x)noexcept
{
	if(x>20)
	{
		return 0;
	}
	if(x<2)
	{
		return 1;
	}
	uint64 result=x;
	for(uint8 i=2; i<=x; ++i)
	{
		result*=i;
	}
	return result;
}
uint32 GCD(uint32 a,uint32 b)noexcept
{
	uint32 zbytek=0;
	for(;;)
	{
		zbytek=a%b;
		if(zbytek==0)
		{
			return b;
		}
		else
		{
			a=b;
			b=zbytek;
		}
	}
}
uint32 LCM(uint32 a, uint32 b)noexcept
{
	return a*b/GCD(a,b);
}

template<typename T>
T ArithmeticProgression(T first, T lenght, T step=T(1))
{
	return lenght*(2*first+step*(lenght-1))/2;
}
}