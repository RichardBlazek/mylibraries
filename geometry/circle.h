#pragma once

#include "geometry/base.h"

namespace geometry
{
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
}