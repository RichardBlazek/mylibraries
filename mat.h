#pragma once

#include "types.h"

namespace math
{
constexpr double pi=3.141592653589793;

template<typename Float>
constexpr Float DegToRad(Float deg)noexcept
{
	return deg*pi/180;
}
template<typename Float>
constexpr Float RadToDeg(Float rad)noexcept
{
	return rad*180/pi;
}
template<typename Num>
constexpr Num Abs(Num val)noexcept
{
	return (val>0)?val:-val;
}

template<typename Num, typename Int>
constexpr Num RoundDown(Num value, Num unit)
{
    return Int(value/unit)*unit;
}
template<typename Num, typename Int>
constexpr Num RoundUp(Num value, Num unit)noexcept
{
	return Int(value/unit)*unit+(value/unit>Num(Int(value/unit)));
}
template<typename Num, typename Int>
constexpr Int Round(Num x)noexcept
{
	return Int(x)+(x-Int(x)>=0.5);
}

template<typename Num, typename Int>
constexpr Num Modulo(Num x, Num div)
{
	return (x/div-Int(x/div))*div;
}
template<typename Int>
Int GCD(Int a, Int b)noexcept
{
	Int rem=a%b;
	while(rem!=0)
	{
		a=b;
		b=rem;
		rem=a%b;
	}
	return b;
}
uint32 LCM(uint32 a, uint32 b)noexcept
{
	return a*b/GCD(a,b);
}

template<typename T>
constexpr T ArithmeticProgression(T first, T lenght, T step=T(1))noexcept
{
	return lenght*(first+step*(lenght-1)/2);
}
}