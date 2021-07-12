#pragma once

#include "base.h"
#include "angle.h"

namespace geometry
{
	namespace coordinates
	{
		template<typename typ>
		struct Cartesian
		{
			typ x=0;
			typ y=0;
			constexpr Cartesian()=default;
			constexpr Cartesian(typ xpos, typ ypos)
				:x(xpos), y(ypos) {}

			template<typename T>
			constexpr Cartesian(const Cartesian<T>& second)
				:Cartesian(T(second.x), T(second.y)) {}
			constexpr double Distance()const noexcept
			{
				return std::sqrt(x*x+y*y);
			}
			constexpr bool operator==(const Cartesian& second)const noexcept
			{
				return x==second.x&&y==second.y;
			}
			constexpr bool operator!=(const Cartesian& second)const noexcept
			{
				return x!=second.x||y!=second.y;
			}
			constexpr Cartesian operator-()const noexcept
			{
				return Cartesian(-x, -y);
			}
			constexpr Cartesian operator~()const noexcept
			{
				return Cartesian(y, x);
			}
			constexpr Cartesian operator-(const Cartesian& second)const noexcept
			{
				return Cartesian(x-second.x, y-second.y);
			}
			constexpr Cartesian operator+(const Cartesian& second)const noexcept
			{
				return Cartesian(x+second.x, y+second.y);
			}
			constexpr Cartesian operator*(const Cartesian& second)const noexcept
			{
				return Cartesian(x*second.x, y*second.y);
			}
			constexpr Cartesian operator/(const Cartesian& second)const noexcept
			{
				return Cartesian(x/second.x, y/second.y);
			}
			template<typename T>
			constexpr Cartesian operator*(T second)const noexcept
			{
				return Cartesian(x*second, y*second);
			}
			template<typename T>
			constexpr Cartesian operator/(T second)const noexcept
			{
				return Cartesian(x/second, y/second);
			}
			//Prirazovani
			constexpr Cartesian operator-=(const Cartesian& second)noexcept
			{
				return *this=*this-second;
			}
			constexpr Cartesian operator+=(const Cartesian& second)noexcept
			{
				return *this=*this+second;
			}
			constexpr Cartesian operator*=(const Cartesian& second)noexcept
			{
				return *this=*this*second;
			}
			constexpr Cartesian operator/=(const Cartesian& second)noexcept
			{
				return *this=*this/second;
			}
			template<typename T>
			constexpr Cartesian operator*=(T second)noexcept
			{
				return *this=*this*second;
			}
			template<typename T>
			constexpr Cartesian operator/=(T second)noexcept
			{
				return *this=*this/second;
			}
		};
		template<typename length_typ, typename Real>
		struct Polar
		{
			using angle_typ=Angle<Real>;
			length_typ lenght=0;
			angle_typ angle;
			constexpr Polar()=default;
			constexpr Polar(length_typ lenght, angle_typ angle)
				:lenght(lenght), angle(angle) {}
			template<typename point_typ>
			constexpr Polar(const Cartesian<point_typ>& cart)
			{
				lenght=std::sqrt(std::abs(cart.x*cart.x+cart.y*cart.y));
				angle=std::atan2(cart.y, cart.x);
			}
			template<typename point_typ>
			constexpr operator Cartesian<point_typ>()const
			{
				return Cartesian<point_typ>(lenght*angle.cos(), lenght*angle.sin());
			}
			constexpr bool operator==(const Polar& second)const noexcept
			{
				return lenght==second.lenght&&angle==second.angle;
			}
			constexpr bool operator!=(const Polar& second)const noexcept
			{
				return lenght!=second.lenght||angle!=second.angle;
			}
			//Zmeny
			constexpr Polar operator-()const noexcept
			{
				return Polar(lenght, angle+pi<Real>);
			}
			constexpr Polar operator*(length_typ second)const noexcept
			{
				return Polar(lenght*second, angle);
			}
			constexpr Polar operator/(length_typ second)const noexcept
			{
				return Polar(lenght/second, angle);
			}
			friend constexpr Polar operator*(length_typ first, const Polar& second)noexcept
			{
				return Polar(first*second.lenght, second.angle);
			}
			Polar Turn(const angle_typ& ang)const
			{
				return Polar(lenght, angle+ang);
			}
			//Prirazovani
			constexpr Polar operator*=(length_typ second)noexcept
			{
				return *this=*this*second;
			}
			constexpr Polar operator/=(length_typ second)noexcept
			{
				return *this=*this/second;
			}
		};
	}
	template<typename T>
	using Point=coordinates::Cartesian<T>;
}
namespace func
{
	template<typename T, typename T2>
	geometry::Point<T> Min(const geometry::Point<T>& p1, const geometry::Point<T2>& p2)
	{
		return geometry::Point<T>(Min(p1.x, p2.x), Min(p1.y, p2.y));
	}
	template<typename T, typename T2>
	geometry::Point<T> Max(const geometry::Point<T>& p1, const geometry::Point<T2>& p2)
	{
		return geometry::Point<T>(Max(p1.x, p2.x), Max(p1.y, p2.y));
	}
}