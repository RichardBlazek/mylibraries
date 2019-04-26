#pragma once

#include "geometry.h"

template<typename Int, typename Float>
class Positioning
{
private:
	class Ratio
	{
	private:
		geometry::Point<Int> object_size;
		geometry::Rect<Int> area;
	public:
		Ratio(geometry::Point<Int> object_size, geometry::Rect<Int> area)
			:object_size(object_size), area(area) {}
		Float Zoom()const
		{
			return func::Min(Float(area.w)/object_size.x, Float(area.h)/object_size.y);
		}
		geometry::Rect<Int> Area()const
		{
			return area;
		}
		geometry::Point<Int> ObjectSize()const
		{
			return object_size;
		}
		void ResizeObject(geometry::Point<Int> size)
		{
			object_size=size;
		}
		void ResizeArea(geometry::Point<Int> size)
		{
			area=area.WithSize(size);
		}
	};
	class Zooming
	{
	private:
		Float zoom=1.0;
		geometry::Point<Float> center;
	public:
		Zooming(geometry::Point<Int> object_size):center(object_size/2) {}
		Float Zoom()const
		{
			return zoom;
		}
		geometry::Point<Float> Center()const
		{
			return center;
		}
		void Displace(geometry::Point<Float> displacement)
		{
			center-=displacement;
		}
		void ChangeZoom(Float change, geometry::Point<Float> zoom_point, Float min_zoom, Float max_zoom)
		{
			if(zoom*change>min_zoom&&zoom*change<max_zoom)
			{
				center=zoom_point-(zoom_point-center)/change;
				zoom*=change;
			}
		}
	};
	Ratio ratio;
	Zooming zoom;
	geometry::Point<Int> Center()const
	{
		return zoom.Center()*Zoom();
	}
	geometry::Point<Int> ObjectSize()const
	{
		return ratio.ObjectSize()*Zoom();
	}
	geometry::Point<Int> ObjectPosition()const
	{
        return ratio.Area().Size()/2-Center();
	}
	Float Zoom()const
	{
		return ratio.Zoom()*zoom.Zoom();
	}
public:
    Positioning(geometry::Point<Int> image_size, geometry::Rect<Int> screen_area)
		:ratio(image_size, screen_area), zoom(image_size) {}
	geometry::Point<Int> ToObject(geometry::Point<Int> xy)const
	{
		return (xy-ObjectPosition()-ratio.Area().Position())/Zoom();
	}
	geometry::Point<Int> ToScreen(geometry::Point<Int> xy)const
	{
		return xy*Zoom()+ObjectPosition();
	}
	geometry::Rect<Int> ToObject(geometry::Rect<Int> xy)const
	{
		return geometry::Rect<Int>(ToObject(xy.Position()), xy.Size()*Zoom());
	}
	geometry::Rect<Int> ToScreen(geometry::Rect<Int> xy)const
	{
		return geometry::Rect<Int>(ToScreen(xy.Position()), xy.Size()*Zoom());
	}
	geometry::Rect<Int> ObjectArea()const
	{
		return geometry::Rect<Int>(ObjectPosition(), ObjectSize());
	}
	void Displace(geometry::Point<Int> displacement)
	{
		zoom.Displace(geometry::Point<Float>(displacement)/Zoom());
	}
	void ChangeZoom(Float change, geometry::Point<Int> zoom_point, Float min_zoom, Float max_zoom)
	{
		zoom.ChangeZoom(change, ToObject(zoom_point), min_zoom/ratio.Zoom(), max_zoom/ratio.Zoom());
	}
	void ResizeObject(geometry::Point<Int> size)
	{
		ratio.ResizeObject(size);
		zoom=Zooming(size);
	}
	void ResizeArea(geometry::Point<Int> size)
	{
		ratio.ResizeArea(size);
		zoom=Zooming(ratio.ObjectSize());
	}
};