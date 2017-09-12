#pragma once

template<typename Repr, Repr unit>
class Fixed
{
private:
	Repr value;
public:
	Fixed() :value(Repr()) {}
	Fixed(const Fixed&)=default;
	Fixed& operator=(const Fixed&)=default;

	template<typename Numeric>
	Fixed(Numeric num): value(Repr(num*unit)) {}

	operator Repr()const
	{
		return value/unit;
	}
	operator float()const
	{
		return float(value)/unit;
	}
	operator double()const
	{
		return double(value)/unit;
	}
	operator long double()const
	{
		return (long double)(value)/unit;
	}
	Fixed operator+(Fixed second)const
	{
		return Fixed(value+second.value);
	}
	Fixed operator-(Fixed second)const
	{
		return Fixed(value-second.value);
	}
	Fixed operator*(Fixed second)const
	{
		return Fixed(value*second.value);
	}
	Fixed operator/(Fixed second)const
	{
		return Fixed(value/second.value);
	}

	Fixed& operator+=(Fixed second)
	{
		value+=second.value;
		return *this;
	}
	Fixed& operator-=(Fixed second)
	{
		value-=second.value;
		return *this;
	}
	Fixed& operator*=(Fixed second)
	{
		value*=second.value;
		return *this;
	}
	Fixed& operator/=(Fixed second)
	{
		value/=second.value;
		return *this;
	}

	bool operator==(Fixed second)const
	{
		return value==second.value;
	}
	bool operator!=(Fixed second)const
	{
		return value!=second.value;
	}
	bool operator<(Fixed second)const
	{
		return value<second.value;
	}
	bool operator>(Fixed second)const
	{
		return value>second.value;
	}
	bool operator<=(Fixed second)const
	{
		return value<=second.value;
	}
	bool operator>=(Fixed second)const
	{
		return value>=second.value;
	}
}