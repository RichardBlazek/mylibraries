#pragma once

#include "base.h"
#include "point.h"
#include "line.h"

namespace geometry
{
	template<typename pos_type>
	struct Rect
	{
		static_assert(std::is_arithmetic_v<pos_type>, "Position must have arithmetic type!");

		using size_type=std::make_unsigned_t<pos_type>;
		using XY=Point<pos_type>;
		using WH=Point<size_type>;

		pos_type x=0, y=0;
		size_type w=0, h=0;

		Rect()=default;
		Rect(pos_type x, pos_type y, size_type w, size_type h)noexcept
			:x(x), y(y), w(w), h(h){}
		template<typename pos_typ>
		Rect(Point<pos_typ> xy, size_type w, size_type h)noexcept :Rect(xy.x, xy.y, w, h){}
		template<typename size_typ>
		Rect(pos_type x, pos_type y, Point<size_typ> wh)noexcept :Rect(x, y, wh.x, wh.y){}
		template<typename pos_typ, typename size_typ>
		Rect(Point<pos_typ> xy, Point<size_typ> wh)noexcept :Rect(xy, wh.x, wh.y){}
		//Square
		Rect(pos_type x, pos_type y, size_type size)noexcept :Rect(x, y, size, size){}
		template<typename pos_typ>
		Rect(Point<pos_typ> xy, size_type size)noexcept :Rect(xy, size, size){}
		//Only size
		Rect(size_type w, size_type h)noexcept :Rect(0, 0, w, h){}
		template<typename size_typ>
		Rect(Point<size_typ> wh)noexcept :Rect(0, 0, wh){}

		template<typename pos_typ>
		bool Encloses(const Point<pos_typ>& point)const noexcept
		{
			return point.x>=x&&point.x<Right()&&point.y>=y&&point.y<Down();
		}
		static Rect Enclose(const std::vector<Point<pos_type>>& points)noexcept
		{
			if(points.empty())
			{
				return Rect();
			}
			XY min=points[0], max=points[0];
			for(size_t i=1;i<points.size();++i)
			{
				min=XY(func::Min(points[i].x, min.x), func::Min(points[i].y, min.y));
				max=XY(func::Max(points[i].x, max.x), func::Max(points[i].y, max.y));
			}
			return Rect(min, max-min);
		}
		template<typename... PosTypes>
		static Rect Enclose(const PosTypes&... points)noexcept
		{
			static_assert(sizeof...(PosTypes)>1, "Function requires at least two parameters");
			XY min=XY(func::Min(points.x...), func::Min(points.y...));
			XY max=XY(func::Max(points.x...), func::Max(points.y...));
			return Rect(min, max-min);
		}
		bool IsEmpty()const noexcept
		{
			return Content()==0;
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
			return XY(Left(), Up());
		}
		XY RightUp()const noexcept
		{
			return XY(Right(), Up());
		}
		XY LeftDown()const noexcept
		{
			return XY(Left(), Down());
		}
		XY RightDown()const noexcept
		{
			return XY(Right(), Down());
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
		size_type Content()const noexcept
		{
			return w*h;
		}

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
		bool Intersects(const Rect& second)const noexcept
		{
			return bool((*this)*second);
		}
		Rect WithSize(WH size)const noexcept
		{
			return Rect(Position(), size);
		}
		Rect WithPosition(XY pos)const noexcept
		{
			return Rect(pos, Size());
		}
		Rect WithWidth(size_type width)const noexcept
		{
			return WithSize(WH(width, h));
		}
		Rect WithHeight(size_type height)const noexcept
		{
			return WithSize(WH(w, height));
		}
		Rect WithCenter(XY center)const noexcept
		{
			return WithPosition(center-Size()/2);
		}
		template<typename size_typ>Rect Extended(Point<size_typ> size_difference)const noexcept
		{
			return Rect(Size()+size_difference).WithCenter(Center());
		}
		template<typename size_typ>Rect Narrowed(Point<size_typ> size_difference)const noexcept
		{
			return Rect(Size()-size_difference).WithCenter(Center());
		}
		bool Near(const Rect& second)const noexcept
		{
			return Extended(XY(2,2)).Intersects(second);
		}
		//Intersection
		Optional<Rect> operator*(const Rect& second)const noexcept
		{
			if(IsEmpty())
			{
				return Optional<Rect>();
			}
			pos_type left=func::Max(x, second.x), right=func::Min(Right(), second.Right());
			pos_type up=func::Max(y, second.y), down=func::Min(Down(), second.Down());
			return (right<left||down<up)?Optional<Rect>():Optional<Rect>(Rect(left, up, right-left, down-up));
		}
		//Union
		Rect operator+(const Rect& second)const noexcept
		{
			if(IsEmpty())
			{
				return second;
			}
			pos_type left=func::Min(x, second.x), right=func::Max(Right(), second.Right());
			pos_type up=func::Min(y, second.y), down=func::Max(Down(), second.Down());
			return Rect(left, up, right-up, down-up);
		}
		Rect operator+(XY shift)const noexcept
		{
			return Rect(Position()+shift, Size());
		}
		Rect operator-(XY shift)const noexcept
		{
			return Rect(Position()-shift, Size());
		}
		Rect& operator+=(XY shift)noexcept
		{
			return *this=*this+shift;
		}
		Rect& operator-=(XY shift)noexcept
		{
			return *this=*this-shift;
		}
	};
}