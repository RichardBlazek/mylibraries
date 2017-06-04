#pragma once

struct Rect
{
	int x=0,y=0, w=0,h=0;
	Rect()=default;
	Rect(int x, int y, int w, int h)noexcept:x(x),y(y),w(w),h(h){}
	Rect(Point xy, int w, int h)noexcept:Rect(xy.x, xy.y, w, h){}
	Rect(int x, int y, Point wh)noexcept:Rect(x, y, wh.x, wh.y){}
	Rect(Point xy, Point wh)noexcept:Rect(xy, wh.x, wh.y){}
	Rect(SDL_Rect rect)noexcept:Rect(rect.x, rect.y, rect.w, rect.h){}
    operator SDL_Rect()const noexcept
	{
		return SDL_Rect{x,y,w,h};
	}
    ///Functions for easy manipulation with Rectangle
    bool IsEnclosingPoint(const Point& point)const noexcept
	{
		return point.x>=x&&point.x<=x+w&&point.y>=y&&point.y<=y+h;
	}
    ///Returns smallest Rectangle enclosing a set of points['points']
    static Rect EnclosePoints(const Point* points, size_t count)noexcept
	{
		if(count==0)
		{
			return Rect();
		}
		Point min=points[0];
		Point max=points[0];
		for(size_t i=1;i<count;++i)
		{
			min.x=func::Min(points[i].x, min.x);
			min.y=func::Min(points[i].y, min.y);
			max.x=func::Max(points[i].x, max.x);
			max.x=func::Max(points[i].x, max.x);
		}
		return Rect(min, max-min);
	}
    ///If widht or height is equal to zero, this function returns [true]
	bool IsEmpty()const noexcept
	{
		return w==0||h==0;
	}
	Point Center()const noexcept
	{
		return Point{x+w/2, y+h/2};
	}
	Point Position()const noexcept
	{
		return Point{x, y};
	}
	Point Size()const noexcept
	{
		return Point{w, h};
	}
	uint32 Content()const noexcept
	{
		return std::abs(w)*std::abs(h);
	}
    ///Compare two Rectangles
    bool operator==(const Rect& rectangle)const noexcept
	{
		return x==rectangle.x&&y==rectangle.y&&w==rectangle.w&&h==rectangle.h;
	}
	bool operator!=(const Rect& rectangle)const noexcept
	{
		return !(*this==rectangle);
	}
	bool operator>(const Rect& rectangle)const noexcept
	{
		return Content()>rectangle.Content();
	}
	bool operator<(const Rect& rectangle)const noexcept
	{
		return Content()<rectangle.Content();
	}
	bool operator>=(const Rect& rectangle)const noexcept
	{
		return Content()>=rectangle.Content();
	}
	bool operator<=(const Rect& rectangle)const noexcept
	{
		return Content()<=rectangle.Content();
	}
    ///If [this] and ['rectangle'] have intersection, this function returns [true]
    bool HasIntersectionWith(const Rect& rectangle)const noexcept
	{
		SDL_Rect r1=*this, r2=rectangle;
		return SDL_HasIntersection(&r1, &r2);
	}
    ///This function returns intersection of [this] and ['rectangle']
    Rect SDL_IntersectWith(const Rect& rectangle)const noexcept
	{
		SDL_Rect r1=*this, r2=rectangle, r3;
		SDL_IntersectRect(&r1, &r2, &r3);
		return Rect(r3);
	}
    ///This function returns intersection of [this] and ['rectangle']
    Rect IntersectWith(const Rect& rectangle)const noexcept
	{
		Rect sdl_intersect=SDL_IntersectWith(rectangle);
        return sdl_intersect.SDL_IntersectWith(*this).IsEmpty()?Rect():sdl_intersect;
	}
    ///This function returns union of [this] and ['rectangle']
    Rect UnionWith(const Rect& rectangle)const noexcept
	{
		SDL_Rect r1=*this, r2=rectangle, r3;
		SDL_UnionRect(&r1, &r2, &r3);
		return Rect(r3);
	}
    bool IntersectWithLine(Line& line)const noexcept
	{
		SDL_Rect rect=*this;
		return SDL_IntersectRectAndLine(&rect, &line.begin.x, &line.begin.y, &line.end.x, &line.end.y);
	}
};