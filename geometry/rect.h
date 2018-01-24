#pragma once

#include "base.h"
#include "point.h"
#include "line.h"

namespace geometry
{
	template<typename pos_type, typename size_type>
	struct Rect
	{
		static_assert(std::is_arithmetic_v<pos_type>&&std::is_arithmetic_v<size_type>, "Position and size must be arithmetic!");
		static_assert(std::is_unsigned_v<size_type>, "Size must be unsigned!");

		using XY=Point<pos_type>;
		using WH=Point<size_type>;

		pos_type x=0, y=0;
		size_type w=0, h=0;

		Rect()=default;
		Rect(pos_type x, pos_type y, size_type w, size_type h)noexcept
			:x(x), y(y), w(w), h(h){}
		template<typename pos_typ> Rect(Point<pos_typ> xy, size_type w, size_type h)noexcept
			:Rect(xy.x, xy.y, w, h){}
		template<typename size_typ> Rect(pos_type x, pos_type y, Point<size_typ> wh)noexcept
			:Rect(x, y, wh.x, wh.y){}
		template<typename pos_typ, typename size_typ> Rect(Point<pos_typ> xy, Point<size_typ> wh)noexcept
			:Rect(xy, wh.x, wh.y){}
		//Square
		Rect(pos_type x, pos_type y, size_type size)noexcept
			:Rect(x, y, size, size){}
		template<typename pos_typ> Rect(Point<pos_typ> xy, size_type size)noexcept
			:Rect(xy, size, size){}
		//Only size
		Rect(size_type w, size_type h)noexcept
			:Rect(0, 0, w, h){}
		template<typename size_typ> Rect(Point<size_typ> wh)noexcept
			:Rect(0, 0, wh){}

		///Functions for easy manipulation with Rectangle
		template<typename pos_typ>
		bool Encloses(const Point<pos_typ>& point)const noexcept
		{
			return point.x>=x&&point.x<=pos_typ(x+w)&&point.y>=y&&point.y<=pos_typ(y+h);
		}
		///Returns smallest Rectangle enclosing a set of points['points']
		template<typename pos_typ>
		static Rect Enclose(const std::vector<Point<pos_typ>>& points)noexcept
		{
			if(points.empty())
			{
				return Rect();
			}
			Point<pos_typ> min=points[0], max=points[0];
			for(size_t i=1;i<points.size();++i)
			{
				min=XY(func::Min(points[i].x, min.x), func::Min(points[i].y, min.y));
				max=XY(func::Max(points[i].x, max.x), func::Max(points[i].y, max.y));
			}
			return Rect(min, max-min);
		}
		///If widht or height is equal to zero, this function returns [true]
		bool IsEmpty()const noexcept
		{
			return w*h==0;
		}
		XY Center()const noexcept
		{
			return XY(x+w/2, y+h/2);
		}
		XY Position()const noexcept
		{
			return XY(x, y);
		}
		WH Size()const noexcept
		{
			return WH(w, h);
		}
		XY LeftUp()const noexcept
		{
			return XY(x, y);
		}
		XY RightUp()const noexcept
		{
			return XY(x+w, y);
		}
		XY LeftDown()const noexcept
		{
			return XY(x, y+h);
		}
		XY RightDown()const noexcept
		{
			return XY(x+w, y+h);
		}
		pos_type Left()const noexcept
		{
			return x;
		}
		pos_type Up()const noexcept
		{
			return y;
		}
		pos_type Right()const noexcept
		{
			return x+w;
		}
		pos_type Down()const noexcept
		{
			return y+h;
		}
		uint32 Content()const noexcept
		{
			return std::abs(w)*std::abs(h);
		}
		///Compare two Rectangles
		bool operator==(const Rect& second)const noexcept
		{
			return x==second.x&&y==second.y&&w==second.w&&h==second.h;
		}
		bool operator!=(const Rect& second)const noexcept
		{
			return x!=second.x||y!=second.y||w!=second.w||h!=second.h;
		}
		bool operator>(const Rect& second)const noexcept
		{
			return Content()>second.Content();
		}
		bool operator<(const Rect& second)const noexcept
		{
			return Content()<second.Content();
		}
		bool operator>=(const Rect& second)const noexcept
		{
			return Content()>=second.Content();
		}
		bool operator<=(const Rect& second)const noexcept
		{
			return Content()<=second.Content();
		}
		///If [this] and ['second'] have intersection, this function returns [true]
		bool Intersects(const Rect& second)const noexcept
		{
			return bool(IntersectWith(second));
		}
		bool Near(const Rect& second)const noexcept
		{
			return Rect(x-1, y-1, w+2, h+2).Intersects(second);
		}
		///This function returns intersection of [this] and ['second']
		Optional<Rect> IntersectWith(const Rect& second)const noexcept
		{
			pos_type left=func::Max(x, second.x), right=func::Min(Right(), second.Right());
			pos_type up=func::Max(y, second.y), down=func::Min(Down(), second.Down());
			return (right<left||down<up)?Optional<Rect>():Optional<Rect>(Rect(left, up, right-left, down-up));
		}
		///This function returns union of [this] and ['second']
		Rect UnionWith(const Rect& second)const noexcept
		{
			pos_type left=func::Min(x, second.x), right=func::Max(Right(), second.Right());
			pos_type up=func::Min(y, second.y), down=func::Max(Down(), second.Down());
			return Rect(left, up, right-up, down-up);
		}
		Rect operator+(XY shift)const
		{
			return Rect(Position()+shift, Size());
		}
		Rect operator-(XY shift)const
		{
			return Rect(Position()-shift, Size());
		}
		Rect& operator+=(XY shift)
		{
			return *this=*this+shift;
		}
		Rect& operator-=(XY shift)
		{
			return *this=*this-shift;
		}
	};
}