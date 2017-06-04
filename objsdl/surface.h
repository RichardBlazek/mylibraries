#pragma once

Surface::Surface(int widht, int height, int depth, const Color* colors, size_t count):surface(nullptr)
{
	Create(widht, height, depth, colors, count);
}
Surface::Surface(int widht, int height, int depth, const Color* colors, size_t count, Pixel::Format format):surface(nullptr)
{
	Create(widht, height, depth, colors, count, format);
}
Surface::Surface(int width, int height, int depth, Masks masks):surface(nullptr)
{
	Create(width, height, depth, masks);
}
Surface::Surface(int width, int height, int depth, Masks masks, Pixel::Format format):surface(nullptr)
{
	Create(width, height, depth, masks, format);
}
Surface Surface::Clone()
{
	Surface result(Width(), Height(), BitsPerPixel(), GetMasks());
	std::copy((uint8*)surface->pixels, (uint8*)surface->pixels+BytesPerLine()*Height(), (uint8*)result.surface->pixels);
	return (Surface&&)result;
}
void Surface::Create(int width, int height, int depth, const Color* colors, size_t count)
{
    Destroy();
    surface=SDL_CreateRGBSurface(0,width,height,depth, 0, 0, 0, 0);
	Error::IfZero(surface);
	if(colors)
		SetPalette(colors, count);
}
void Surface::Create(int width, int height, int depth, const Color* colors, size_t count, Pixel::Format format)
{
	Destroy();
    surface=SDL_CreateRGBSurfaceWithFormat(0,width,height,depth, uint32(format));
	Error::IfZero(surface);
	if(colors)
		SetPalette(colors, count);
}
void Surface::Create(int width, int height, int depth, Masks masks)
{
    Destroy();
    surface=SDL_CreateRGBSurface(0,width,height,depth, BE_ToNative(masks.r), BE_ToNative(masks.g), BE_ToNative(masks.b), BE_ToNative(masks.a));
	Error::IfZero(surface);
}
void Surface::Create(int width, int height, int depth, Masks masks, Pixel::Format format)
{
    Destroy();
    surface=SDL_CreateRGBSurfaceWithFormat(0,width,height,depth, uint32(format));
	Error::IfZero(surface);
}
void Surface::Blit(Surface& second, const Rect* source, const Rect* destination)
{
	SDL_Rect r1=source?*source:Rect(), r2=destination?*destination:Rect();
    Error::Condition(SDL_BlitSurface(surface, source?&r1:nullptr, second.surface, destination?&r2:nullptr)<0);
}
void Surface::Paste(Surface& second, const Rect* source, const Rect* destination)
{
	SDL_Rect r1=source?*source:Rect(), r2=destination?*destination:Rect();
    Error::Condition(SDL_BlitScaled(surface, source?&r1:nullptr, second.surface, destination?&r2:nullptr)<0);
}
void Surface::EnableColorKey(const Color& col)
{
	Error::Condition(SDL_SetColorKey(surface, true, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a))<0);
}
void Surface::DisableColorKey(const Color& col)
{
	Error::Condition(SDL_SetColorKey(surface, false, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a))<0);
}
void Surface::SetRGBMod(const Color::WithoutAlpha& col)
{
	Error::Condition(SDL_SetSurfaceColorMod(surface, col.r, col.g, col.b)<0);
}
void Surface::SetAlphaMod(uint8 alpha)
{
	Error::Condition(SDL_SetSurfaceAlphaMod(surface, alpha)<0);
}
void Surface::SetRGBAMod(const Color& col)
{
	SetRGBMod(col);
	SetAlphaMod(col.a);
}
bool Surface::MustLock()const noexcept
{
	return SDL_MUSTLOCK(surface);
}
#undef SDL_MUSTLOCK
void Surface::Lock()
{
	Error::IfNegative(SDL_LockSurface(surface));
}
void Surface::Unlock()noexcept
{
	SDL_UnlockSurface(surface);
}
void Surface::EnableRLE()
{
    Error::IfNegative(SDL_SetSurfaceRLE(surface, true));
}
void Surface::DisableRLE()
{
    Error::IfNegative(SDL_SetSurfaceRLE(surface, false));
}
void Surface::SetBlendMode(BlendMode mode)
{
    Error::IfNegative(SDL_SetSurfaceBlendMode(surface, SDL_BlendMode(mode)));
}
void Surface::Repaint(const Color& col)
{
	Error::IfNegative(SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a)));
}
void Surface::DrawLine(const Line& line, const Color& col)
{
	auto TransformTo45=[](Point pos, uint8 convf)->Point
	{
		return	convf==1?pos:
				convf==2?Point(pos.y, pos.x):
				convf==3?Point(pos.y, -pos.x):
				convf==4?Point(-pos.x, pos.y):
				convf==5?Point(-pos.x, -pos.y):
				convf==6?Point(-pos.y, -pos.x):
				convf==7?Point(-pos.y, pos.x):
						Point(pos.x, -pos.y);
	};
	auto TransformFrom45=[](Point pos, uint8 convf)->Point
	{
		return	convf==1?pos:
				convf==2?Point(pos.y, pos.x):
				convf==7?Point(pos.y, -pos.x):
				convf==4?Point(-pos.x, pos.y):
				convf==5?Point(-pos.x, -pos.y):
				convf==6?Point(-pos.y, -pos.x):
				convf==3?Point(-pos.y, pos.x):
						Point(pos.x, -pos.y);
	};
	Point d(line.end.x-line.begin.x, line.end.y-line.begin.y);
	uint8 convf=0;
	if(d.x>0&&d.y>0&&d.x>=d.y)
		convf=1;
	else if(d.x>0&&d.y>0&&d.x<d.y)
		convf=2;
	else if(d.x<=0&&d.y>0&& -d.x<d.y)
		convf=3;
	else if(d.x<=0&&d.y>0&& -d.x>=d.y)
		convf=4;
	else if(d.x<=0&&d.y<=0&& -d.x>= -d.y)
		convf=5;
	else if(d.x<=0&&d.y<=0&& -d.x< -d.y)
		convf=6;
	else if(d.x>0&&d.y<=0&&d.x< -d.y)
		convf=7;
	else
		convf=8;
	const Line transformed(TransformTo45(line.begin, convf), TransformTo45(line.end, convf));
	const Point diff(transformed.end-transformed.begin);
	const Point d2=diff*2;
	int predictor=d2.y-diff.x;
	for(Point point=transformed.begin;point.x<=transformed.end.x;++point.x)
	{
		SetPixel(TransformFrom45(point, convf), col);
		if(predictor>=0)
		{
			++point.y;
			predictor+=d2.y-d2.x;
		}
		else
		{
			predictor+=d2.y;
		}
	}
}
void Surface::DrawRect(const Rect& rect, const Color& col)
{
	for(int i=rect.x, limit=rect.x+rect.w; i<limit;++i)
	{
		SetPixel(Point(i,rect.y), col);
	}
	for(int i=rect.x, limit=rect.x+rect.w; i<limit;++i)
	{
		SetPixel(Point(i,rect.y+rect.h), col);
	}
	for(int i=rect.y, limit=rect.y+rect.h; i<limit;++i)
	{
		SetPixel(Point(rect.x, i), col);
	}
	for(int i=rect.y, limit=rect.y+rect.h; i<limit;++i)
	{
		SetPixel(Point(rect.x+rect.w, i), col);
	}
}
void Surface::FillRect(const Rect& rect, const Color& col)
{
	SDL_Rect r=rect;
	Error::IfNegative(SDL_FillRect(surface, &r, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a)));
}
void Surface::DrawText(Font& font, const std::string& u8text, const Color& textcolor, Point dst)
{
	Surface textimage=font.Render(u8text, textcolor);
	Rect destination(dst, textimage.Size());
	Paste(textimage, nullptr, &destination);
}
void Surface::DrawText(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst)
{
	Surface textimage=font.Render(u16text, textcolor);
	Rect destination(dst, textimage.Size());
	Paste(textimage, nullptr, &destination);
}
void Surface::DrawText(Font& font, char16_t character, const Color& textcolor, Point dst)
{
	Surface textimage=font.Render(character, textcolor);
	Rect destination(dst, textimage.Size());
	Paste(textimage, nullptr, &destination);
}
void Surface::DrawText(Font& font, const std::string& u8text, const Color& textcolor, Point dst, const Color& backgroundcolor)
{
	Surface textimage=font.Render(u8text, textcolor, backgroundcolor);
	Rect destination(dst, textimage.Size());
	Paste(textimage, nullptr, &destination);
}
void Surface::DrawText(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst, const Color& backgroundcolor)
{
	Surface textimage=font.Render(u16text, textcolor, backgroundcolor);
	Rect destination(dst, textimage.Size());
	Paste(textimage, nullptr, &destination);
}
void Surface::DrawText(Font& font, char16_t character, const Color& textcolor, Point dst, const Color& backgroundcolor)
{
	Surface textimage=font.Render(character, textcolor, backgroundcolor);
	Rect destination(dst, textimage.Size());
	Paste(textimage, nullptr, &destination);
}
void Surface::DrawTextFast(Font& font, const std::string& u8text, const Color& textcolor, Point dst)
{
	Surface textimage=font.RenderFast(u8text, textcolor);
	Rect destination(dst, textimage.Size());
	Paste(textimage, nullptr, &destination);
}
void Surface::DrawTextFast(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst)
{
	Surface textimage=font.RenderFast(u16text, textcolor);
	Rect destination(dst, textimage.Size());
	Paste(textimage, nullptr, &destination);
}
void Surface::DrawTextFast(Font& font, char16_t character, const Color& textcolor, Point dst)
{
	Surface textimage=font.RenderFast(character, textcolor);
	Rect destination(dst, textimage.Size());
	Paste(textimage, nullptr, &destination);
}