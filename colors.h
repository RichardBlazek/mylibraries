#pragma once

#include "types.h"

namespace colors
{
    struct RGB
    {
        uint8 r=0, g=0, b=0;
        constexpr RGB()=default;
        constexpr RGB(uint8 r, uint8 g, uint8 b):r(r), g(g), b(b) {}
		constexpr uint16 Brightness()const
		{
			return uint16(r)+g+b;
		}
		constexpr bool operator==(const RGB& second)const
		{
			return r==second.r&&g==second.g&&b==second.b;
		}
		constexpr bool operator!=(const RGB& second)const
		{
			return r!=second.r||g!=second.g||b!=second.b;
		}
		constexpr RGB operator-(const RGB& second)const
		{
			return RGB(r-second.r, g-second.g, b-second.b);
		}
		static constexpr RGB White()
		{
			return RGB(255,255,255);
		}
		static constexpr RGB Black()
		{
			return RGB(0,0,0);
		}
		static constexpr RGB Red()
		{
			return RGB(255,0,0);
		}
		static constexpr RGB Green()
		{
			return RGB(0,255,0);
		}
		static constexpr RGB Blue()
		{
			return RGB(0,0,255);
		}
		static constexpr RGB Yellow()
		{
			return RGB(255,255,0);
		}
		static constexpr RGB Cyan()
		{
			return RGB(0,255,255);
		}
		static constexpr RGB Magenta()
		{
			return RGB(255,0,255);
		}
    };
    struct RGBA: public RGB
    {
		uint8 a=255;
        constexpr RGBA()=default;
        constexpr RGBA(uint8 r, uint8 g, uint8 b, uint8 a=255):RGB(r,g,b), a(a) {}
        constexpr RGBA(RGB rgb):RGBA(rgb.r, rgb.g, rgb.b) {}
		constexpr bool operator==(const RGBA& second)const
		{
			return RGB::operator==(second)&&a==second.a;
		}
		constexpr bool operator!=(const RGBA& second)const
		{
			return RGB::operator!=(second)||a!=second.a;
		}
    };
}