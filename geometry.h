#pragma once

#include <cmath>

namespace geometry
{
template<typename T>
constexpr T pi=M_PI;

template<typename Float>
constexpr Float RadToDeg(Float x)noexcept
{
	return x*180/pi<Float>;
}
template<typename Float>
constexpr Float DegToRad(Float x)noexcept
{
	return x*pi<Float>/180;
}

template<typename Float>
class Angle
{
private:
	static constexpr Float max=pi<Float>*2;
	Float value=0;
public:
	constexpr Angle()=default;
	constexpr Angle(Float angle)noexcept:value(angle-max*int32(angle/max)){}
	constexpr Angle& operator=(Float angle)noexcept
	{
		return *this=Angle(angle);
	}
	constexpr static Angle FromDeg(Float angle)noexcept
	{
		return Angle(DegToRad(angle));
	}
	//Porovnavani
	constexpr bool operator==(const Angle& second)const noexcept
	{
		return value==second.value;
	}
	constexpr bool operator!=(const Angle& second)const noexcept
	{
		return value!=second.value;
	}
	constexpr bool operator<(const Angle& second)const noexcept
	{
		return value<second.value;
	}
	constexpr bool operator>(const Angle& second)const noexcept
	{
		return value>second.value;
	}
	constexpr bool operator<=(const Angle& second)const noexcept
	{
		return value<=second.value;
	}
	constexpr bool operator>=(const Angle& second)const noexcept
	{
		return value>=second.value;
	}
	//Scitani
	constexpr Angle operator-(const Angle& second)const noexcept
	{
		return Angle(value-second.value);
	}
	constexpr Angle operator+(const Angle& second)const noexcept
	{
		return Angle(value+second.value);
	}
	constexpr Angle operator-=(const Angle& second)noexcept
	{
		return *this=*this-second;
	}
	constexpr Angle operator+=(const Angle& second)noexcept
	{
		return *this=*this+second;
	}
	//Nasobeni
	constexpr Angle operator/(Float second)const noexcept
	{
		return Angle(value/second);
	}
	constexpr Angle operator*(Float second)const noexcept
	{
		return Angle(value*second);
	}
	constexpr Angle operator/=(Float second)noexcept
	{
		return *this=*this/second;
	}
	constexpr Angle operator*=(Float second)noexcept
	{
		return *this=*this*second;
	}
	//Ostatni
	constexpr Float sin()const
	{
		return std::sin(value);
	}
	constexpr Float cos()const
	{
		return std::cos(value);
	}
	constexpr Float InRadians()const noexcept
	{
		return value;
	}
	constexpr Float InDegrees()const noexcept
	{
		return RadToDeg(value);
	}
};

template<typename typ>
struct Point
{
	typ x=0;
	typ y=0;
	constexpr Point()=default;
	constexpr Point(typ xpos, typ ypos)
		:x(xpos), y(ypos){}
	constexpr bool operator==(const Point& second)const noexcept
	{
		return x==second.x&&y==second.y;
	}
	constexpr bool operator!=(const Point& second)const noexcept
	{
		return x!=second.x||y!=second.y;
	}
	constexpr Point operator-(const Point& second)const noexcept
	{
		return Point(x-second.x, y-second.y);
	}
	constexpr Point operator+(const Point& second)const noexcept
	{
		return Point(x+second.x, y+second.y);
	}
	constexpr Point operator*(const Point& second)const noexcept
	{
		return Point(x*second.x, y*second.y);
	}
	constexpr Point operator/(const Point& second)const noexcept
	{
		return Point(x/second.x, y/second.y);
	}
	constexpr Point operator*(typ second)const noexcept
	{
		return Point(x*second, y*second);
	}
	constexpr Point operator/(typ second)const noexcept
	{
		return Point(x/second, y/second);
	}
	//Prirazovani
	constexpr Point operator-=(const Point& second)noexcept
	{
		return *this=*this-second;
	}
	constexpr Point operator+=(const Point& second)noexcept
	{
		return *this=*this+second;
	}
	constexpr Point operator*=(const Point& second)noexcept
	{
		return *this=*this*second;
	}
	constexpr Point operator/=(const Point& second)noexcept
	{
		return *this=*this/second;
	}
	constexpr Point operator*=(typ second)noexcept
	{
		return *this=*this*second;
	}
	constexpr Point operator/=(typ second)noexcept
	{
		return *this=*this/second;
	}
};

template<typename point_typ, typename radius_typ, typename Float>
struct Circle
{
	Point<point_typ> center;
	radius_typ radius=0;
	constexpr Circle()=default;
	constexpr Circle(Point<point_typ> center, radius_typ radius)
		:center(center), radius(radius){}
	constexpr Float Content()const
	{
		return radius*radius*pi<Float>;
	}
	constexpr Float Perimeter()const
	{
        return 2*pi<Float>*radius;
	}
};

template<typename point_typ, typename Float>
struct Line
{
	Point<point_typ> begin;
	Point<point_typ> end;
	constexpr Line()=default;
	constexpr Line(const Point<point_typ>& begin, const Point<point_typ>& end)
		:begin(begin),end(end){}
	constexpr Float Lenght()
	{
		const Point<Float> diff=end-begin;
		return std::sqrt(std::abs(diff.x*diff.x+diff.y*diff.y));
	}
};

template<typename point_typ, typename lenght_typ, typename Float>
struct Vector
{
	Point<point_typ> begin;
	lenght_typ lenght=0;
	Angle<Float> angle;
	constexpr Vector()=default;
	constexpr Vector(Point<point_typ> beg, lenght_typ len, Angle<Float> ang)
		:begin(beg), lenght(len), angle(ang){}
	constexpr explicit Vector(const Line<point_typ, Float>& ln)
	{
		Point<point_typ> diff=ln.end-ln.begin;
		begin=ln.begin;
		lenght=std::sqrt(std::abs(diff.x*diff.x+diff.y*diff.y));
		angle=std::atan2(diff.y, diff.x);
	}
	constexpr explicit operator Line<point_typ, Float>()const
	{
		return Line<point_typ, Float>(begin, Point<point_typ>(point_typ(begin.x+lenght*angle.cos()), point_typ(begin.y+lenght*angle.sin())));
	}
	constexpr Point<point_typ> GetEnd()const
	{
		return Line<point_typ, Float>(*this).end;
	}
	constexpr void Reverse()
	{
		begin=GetEnd();
		angle=angle-pi<Float>;
	}
	constexpr Vector GetReversed()const
	{
		Vector tmp(*this);
		tmp.Reverse();
		return tmp;
	}
};
}