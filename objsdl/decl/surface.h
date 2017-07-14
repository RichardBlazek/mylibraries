#pragma once

enum class BlendMode
{
    None=SDL_BLENDMODE_NONE,
    Blend=SDL_BLENDMODE_BLEND,
    Add=SDL_BLENDMODE_ADD,
    Mod=SDL_BLENDMODE_MOD
};

class Surface
{
private:
    SDL_Surface* surface;
    static inline uint32 BE_ToNative(uint32 num)
	{
		return SDL_SwapBE32(num);
	}
	Surface(SDL_Surface* sdl):surface(sdl){}
public:
	struct Masks
	{
		uint32 r, g, b, a=0;
	};
	friend Window;
	friend Texture;
	friend Renderer;
	friend Cursor;
	friend Font;
    void Destroy()
	{
		if(surface)
		{
			--surface->refcount;
			if(surface->refcount==0)
				SDL_FreeSurface(surface);
			surface=nullptr;
		}
	}
    Surface()noexcept:surface(nullptr){}
    ~Surface()noexcept
	{
		Destroy();
	}
    Surface(const Surface& init):surface(init.surface)
	{
		++surface->refcount;
	}
    Surface& operator=(const Surface& init)
	{
		Destroy();
		surface=init.surface;
		++surface->refcount;
		return *this;
	}
	Surface(Surface&& init)noexcept:surface(init.surface)
	{
		init.surface=nullptr;
	}
    Surface& operator=(Surface&& init)noexcept
	{
		Destroy();
		surface=init.surface;
		init.surface=nullptr;
		return *this;
	}
    Surface(int width, int height, int depth, const Color* colors, size_t count=256);
    Surface(int width, int height, int depth, const Color* colors, size_t count, Pixel::Format format);
    Surface(int width, int height, int depth, Masks masks);
    Surface(int width, int height, int depth, Masks masks, Pixel::Format format);
    Surface Clone();
    void Create(int width, int height, int depth, const Color* colors, size_t count=256);
    void Create(int width, int height, int depth, const Color* colors, size_t count, Pixel::Format format);
	void Create(int width, int height, int depth, Masks masks);
	void Create(int width, int height, int depth, Masks masks, Pixel::Format format);
	static Surface LoadImg(const std::string& file)
	{
		Surface result(Error::IfZero(IMG_Load(file.c_str())));
		return (Surface&&)result;
	}
	static Surface LoadXPM(char** xpm)
	{
		Surface result(Error::IfZero(IMG_ReadXPMFromArray(xpm)));
		return (Surface&&)result;
	}
	void SaveAsBMP(const std::string& file)
	{
		Error::IfNegative(SDL_SaveBMP(surface, file.c_str()));
	}
    uint8 BytesPerPixel()const noexcept
	{
		return surface->format->BytesPerPixel;
	}
    uint8 BitsPerPixel()const noexcept
	{
		return surface->format->BitsPerPixel;
	}
    void SetPalette(const Color* colors, uint32 count)
	{
		if(surface->format->palette)
		{
			SDL_FreePalette(surface->format->palette);
		}
		surface->format->palette=SDL_AllocPalette(count);
		Error::IfZero(surface->format->palette);
		for(size_t i=0, limit=surface->format->palette->ncolors;i<limit;++i)
		{
			surface->format->palette->colors[i]=SDL_Color(colors[i]);
		}
	}
    Masks GetMasks()const
	{
		return Masks{surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask};
	}
private:
	uint8* Index(const Point& xy)const noexcept
	{
		return ((uint8*)surface->pixels)+xy.y*BytesPerLine()+xy.x*BytesPerPixel();
	}
	uint32 GetPixelRawValue(const Point& xy)const
	{
		if(xy.x<0||xy.x>=surface->w||xy.y<0||xy.y>=surface->h)
			throw Error("Surface::GetPixel out of range");
		auto ptr=Index(xy);
		switch(BytesPerPixel())
		{
			case 1:
				return *ptr;
			case 2:
				return *(uint16*)ptr;
			case 3:
				return IsBigEndian?ptr[0]<<16|ptr[1]<<8|ptr[2]:ptr[2]<<16|ptr[1]<<8|ptr[0];
			case 4:
				return *(uint32*)ptr;
		}
		return 0;
	}
	void SetPixelRawValue(const Point& xy, uint32 value)noexcept
	{
		if(xy.x<0||xy.x>surface->w||xy.y<0||xy.y>surface->h)return;
		auto ptr=Index(xy);
		switch(BytesPerPixel())
		{
			case 1:
				*ptr=uint8(value);
				break;
			case 2:
				*(uint16*)ptr=uint16(value);
				break;
			case 3:
				if(IsBigEndian)
				{
					ptr[0]=uint8(value>>16);
					ptr[1]=uint8(value>>8);
					ptr[2]=uint8(value);
				}
				else
				{
					ptr[2]=uint8(value>>16);
					ptr[1]=uint8(value>>8);
					ptr[0]=uint8(value);
				}
				break;
			case 4:
				*(uint32*)ptr=value;
				break;
		}
	}
	Color IndexPalette(size_t i)const noexcept
	{
		return surface->format->palette->colors[i];
	}
public:
	size_t GetPaletteSize()const noexcept
	{
		return surface->format->palette->ncolors;
	}
	void Repaint(const Color& col);
	Color GetPixel(const Point& xy)const
	{
		Color result;
		SDL_GetRGBA(GetPixelRawValue(xy), surface->format, &result.r, &result.g, &result.b, &result.a);
		return result;
	}
	void SetPixel(const Point& xy, const Color& col)
	{
		SetPixelRawValue(xy, SDL_MapRGBA(surface->format, col.r, col.g, col.b, col.a));
	}
	uint8& Index8(const Point& xy)
	{
		if(BitsPerPixel()!=8)
		{
			throw Error("Surface::Index8>This surface is not 8-bit!");
		}
		return *Index(xy);
	}
    void DrawLine(const Line& line, const Color& col);
    void DrawRect(const Rect& rectangle, const Color& col);
    void FillRect(const Rect& rectangle, const Color& col);
    uint32 BytesPerLine()const noexcept
	{
		return surface->pitch;
	}
    uint32 Width()const noexcept
	{
		return surface->w;
	}
    uint32 Height()const noexcept
	{
		return surface->h;
	}
	Point Size()const noexcept
	{
		return Point(Width(), Height());
	}
    bool SetClipRect(const Rect& rectangle)noexcept
	{
		SDL_Rect rect=rectangle;
		return SDL_SetClipRect(surface, &rect);
	}
    void GetClipRect(const Rect& rectangle)noexcept
	{
		SDL_Rect rect=rectangle;
		return SDL_GetClipRect(surface, &rect);
	}
    void Blit(Surface&, const Rect*,const Rect*);
    void Paste(Surface&, const Rect*,const Rect*);
    void EnableColorKey(const Color& col);
    void DisableColorKey(const Color& col);
    void SetRGBMod(const Color::WithoutAlpha& col);
    void SetAlphaMod(uint8 alpha);
    void SetRGBAMod(const Color& col);
    void SetBlendMode(BlendMode mode);
    bool MustLock()const noexcept;
    void Lock();
    void Unlock()noexcept;
    void EnableRLE();
    void DisableRLE();
    Pixel::Format GetFormat()const noexcept
	{
        return Pixel::Format(surface->format->format);
	}
	Surface Convert(Pixel::Format desired)
	{
		Surface result;
		result.surface=SDL_ConvertSurfaceFormat(surface,uint32(desired),0);
		return result;
	}
	void DrawCircle(const Circle& circle, const Color& color)
	{
		Point pos=circle.center;
		float angle=0;
		float angle_stepsize=0.001;
		while(angle<2*pi)
		{
			pos.x=circle.center.x+circle.radius*SDL_cos(angle);
			pos.y=circle.center.y+circle.radius*SDL_sin(angle);
			SetPixel(pos, color);
			angle+=angle_stepsize;
		}
	}
	void DrawText(Font& font, const std::string& u8text, const Color& textcolor, Point dst);
	void DrawText(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst);
	void DrawText(Font& font, char16_t character, const Color& textcolor, Point dst);
	void DrawText(Font& font, const std::string& u8text, const Color& textcolor, Point dst, const Color& backgroundcolor);
	void DrawText(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst, const Color& backgroundcolor);
	void DrawText(Font& font, char16_t character, const Color& textcolor, Point dst, const Color& backgroundcolor);
	void DrawTextFast(Font& font, const std::string& u8text, const Color& textcolor, Point dst);
	void DrawTextFast(Font& font, const std::u16string& u16text, const Color& textcolor, Point dst);
	void DrawTextFast(Font& font, char16_t character, const Color& textcolor, Point dst);
};