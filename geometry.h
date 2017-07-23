#pragma once

#include <cmath>

namespace geometry
{
	template<typename T>
	constexpr T pi=3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588;

	template<typename Real>
	class Angle
	{
	private:
		constexpr static Real RadToDeg(Real x)noexcept
		{
			return x*180/pi<Real>;
		}
		constexpr static Real DegToRad(Real x)noexcept
		{
			return x*pi<Real>/180;
		}
		static constexpr Real max=pi<Real>*2;
		Real value=0;
	public:
		constexpr Angle()=default;
		constexpr Angle(Real angle)noexcept:value(angle-max*int32(angle/max)) {}
		constexpr Angle& operator=(Real angle)noexcept
		{
			return *this=Angle(angle);
		}
		constexpr static Angle FromDeg(Real angle)noexcept
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
		constexpr Angle operator/(Real second)const noexcept
		{
			return Angle(value/second);
		}
		constexpr Angle operator*(Real second)const noexcept
		{
			return Angle(value*second);
		}
		constexpr Angle operator/=(Real second)noexcept
		{
			return *this=*this/second;
		}
		constexpr Angle operator*=(Real second)noexcept
		{
			return *this=*this*second;
		}
		//Ostatni
		constexpr Real sin()const
		{
			return std::sin(value);
		}
		constexpr Real cos()const
		{
			return std::cos(value);
		}
		constexpr Real InRadians()const noexcept
		{
			return value;
		}
		constexpr Real InDegrees()const noexcept
		{
			return RadToDeg(value);
		}
	};

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
			constexpr bool operator==(const Cartesian& second)const noexcept
			{
				return x==second.x&&y==second.y;
			}
			constexpr bool operator!=(const Cartesian& second)const noexcept
			{
				return x!=second.x||y!=second.y;
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
			constexpr Cartesian operator*(typ second)const noexcept
			{
				return Cartesian(x*second, y*second);
			}
			constexpr Cartesian operator/(typ second)const noexcept
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
			constexpr Cartesian operator*=(typ second)noexcept
			{
				return *this=*this*second;
			}
			constexpr Cartesian operator/=(typ second)noexcept
			{
				return *this=*this/second;
			}
		};
		template<typename length_typ, typename Real>
		class Polar
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

	template<typename point_typ, typename radius_typ, typename Real>
	struct Circle
	{
		constexpr static Real pi=geometry::pi<Real>;
		point_typ center;
		radius_typ radius=0;
		constexpr Circle()=default;
		constexpr Circle(point_typ center, radius_typ radius)
			:center(center), radius(radius) {}
		constexpr Real Content()const
		{
			return radius*radius*pi;
		}
		constexpr Real Perimeter()const
		{
			return 2*pi*radius;
		}
	};

	template<typename point_typ, typename length_typ>
	struct Line
	{
		point_typ begin;
		point_typ end;
		constexpr Line()=default;
		constexpr Line(const point_typ& begin, const point_typ& end)
			:begin(begin), end(end) {}
		constexpr length_typ Lenght()const
		{
			return coordinates::Polar<length_typ, int>(end-begin).lenght;
		}
	};

	template<typename point_typ, typename length_typ, typename Real>
	struct Vector
	{
		constexpr static Real pi=geometry::pi<Real>;
		using vector_typ=coordinates::Polar<length_typ, Real>;
		using angle_typ=Angle<Real>;
		using line_typ=Line<point_typ, Real>;
		point_typ begin;
		vector_typ move;
		constexpr Vector()=default;

		constexpr Vector(const point_typ& begin, const vector_typ& move)
			:begin(begin), move(move) {}

		constexpr explicit Vector(const line_typ& ln)
			:begin(ln.begin), move(ln.end-ln.begin){}

		constexpr explicit operator line_typ()const
		{
			return line_typ(begin, begin+point_typ(move));
		}
		constexpr point_typ GetEnd()const
		{
			return line_typ(*this).end;
		}
		constexpr Vector Reverse()const
		{
			return Vector(GetEnd(), move.Turn(angle_typ(-pi)));
		}
	};
}