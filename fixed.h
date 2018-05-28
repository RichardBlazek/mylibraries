#pragma once

template<typename T, T prec>
class Fixed
{
public:
	using Base=T;
	static constexpr Base precision=prec;
private:
	Base value=0;
public:
	template<typename Number>
	Fixed(Number num=Number(0))
		:value(Base(num*precision)) {}
	//Casting
	template<typename Number>
	Number ToNumber()const
	{
		return Number(value)/Number(precision);
	}
	template<typename Tp, Tp preci>
	Fixed<Tp, preci> ToFixed()const
	{
		return Fixed<Tp, preci>(value)/precision;
	}
	//Operace
#define OPERATOR(op)										\
	Fixed& operator op##= (const Fixed& second)				\
	{														\
		value op##= second.value;							\
		return *this;										\
	}														\
	template<typename Number>								\
	Fixed& operator op##= (Number second)					\
	{														\
		value op##= second;									\
		return *this;										\
	}														\
	template<typename Number>								\
	Fixed operator op (Number second)						\
	{														\
		Fixed result=*this;									\
		result op##= second;								\
		return result;										\
	}														\
	template<typename Number>								\
	friend Fixed operator op (Number first, Fixed second)	\
	{														\
		Fixed result=first;									\
		result op##= second;								\
		return result;										\
	}
	OPERATOR(+)
	OPERATOR(-)
	OPERATOR(*)
	OPERATOR(/)
	OPERATOR(%)
	OPERATOR(&)
	OPERATOR(|)
	OPERATOR(^)
	OPERATOR(<<)
	OPERATOR(>>)
#undef OPERATOR
	Fixed operator~()const
	{
		Fixed result;
		result.value=~value;
		return result;
	}
	Fixed operator-()const
	{
		Fixed result;
		result.value=-value;
		return result;
	}
};