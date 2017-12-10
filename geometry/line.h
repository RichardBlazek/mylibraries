#pragma once

#include "base.h"
#include "point.h"
#include "angle.h"

namespace geometry
{
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
		constexpr point_typ Difference()const
		{
			return point_typ{end.x-begin.x, end.y-begin.y};
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
		constexpr Vector(const point_typ& begin, length_typ lenght, Angle<Real> angle)
			:begin(begin), move(lenght, angle) {}

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