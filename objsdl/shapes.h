#pragma once

#include "geometry.h"

constexpr double pi=geometry::pi<double>;

using geometry::RadToDeg;
using geometry::DegToRad;

using Angle=geometry::Angle<double>;
using Point=geometry::Point<int>;
using Line=geometry::Line<int, double>;
using Vector=geometry::Vector<int, double, double>;
using Circle=geometry::Circle<int, double, double>;