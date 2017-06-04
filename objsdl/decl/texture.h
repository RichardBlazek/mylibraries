#pragma once

class Texture
{
private:
    SDL_Texture* texture;
public:
	enum class Access
	{
        Static=SDL_TEXTUREACCESS_STATIC,
        Streaming=SDL_TEXTUREACCESS_STREAMING,
        Target=SDL_TEXTUREACCESS_TARGET
	};
	enum class Modulate: uint8
	{
		None=SDL_TEXTUREMODULATE_NONE,
		Color=SDL_TEXTUREMODULATE_COLOR,
		Alpha=SDL_TEXTUREMODULATE_ALPHA
	};
	struct Info
	{
		Pixel::Format format;
		Access access;
		Point size;
	};
	struct LockedData
	{
        void* pixels;
        int bytesPerLine;
	};
    Texture(const Texture&)=delete;
    Texture& operator=(const Texture&)=delete;
	friend Renderer;
    Texture()noexcept:texture(nullptr){}
    ~Texture()noexcept
	{
		Destroy();
	}
    Texture(Texture&& src)noexcept
			:texture(src.texture)
	{
		src.texture=nullptr;
	}
    Texture& operator=(Texture&& src)noexcept
    {
		texture=src.texture;
		src.texture=nullptr;
		return *this;
	}
    Texture(Renderer& renderer, uint32 format, uint32 access, uint32 w, uint32 h)
		:texture(SDL_CreateTexture(renderer.renderer,format,access,w,h))
	{
		Error::IfZero(texture);
	}
    Texture(Surface surface, Renderer& renderer)
			:texture(SDL_CreateTextureFromSurface(renderer.renderer, surface.surface))
	{
		Error::IfZero(texture);
	}
    void Destroy()noexcept
	{
		if(texture)
		{
			SDL_DestroyTexture(texture);
			texture=nullptr;
		}
	}
    Info GetInfo()const
	{
		Info result;
		Error::IfNegative(SDL_QueryTexture(texture, reinterpret_cast<uint32*>(&result.format), reinterpret_cast<int*>(&result.access), &result.size.x, &result.size.y));
		return result;
	}
    void Update(const Surface& pixels, Point pos=Point(0,0))
	{
		SDL_Rect rectangle{pos.x,pos.y, int(pixels.Width()), int(pixels.Height())};
		Error::IfNegative(SDL_UpdateTexture(texture,&rectangle,pixels.surface->pixels, pixels.BytesPerLine()));
	}
    static Texture LoadImg(const std::string& file, Renderer& rend)
	{
		Texture tmp;
		tmp.texture=IMG_LoadTexture(rend.renderer, file.c_str());
		Error::IfZero(tmp.texture);
		return (Texture&&)tmp;
	}
	void SetRGBMod(const Color& mod)
	{
		Error::Condition(SDL_SetTextureColorMod(texture, mod.r, mod.g, mod.b)<0);
	}
	void SetAlphaMod(uint8 alpha)
	{
		Error::Condition(SDL_SetTextureAlphaMod(texture, alpha)<0);
	}
	void SetRGBAMod(const Color& mod)
	{
		SetRGBMod(mod);
		SetAlphaMod(mod.a);
	}
	void SetBlendMode(BlendMode mode)
	{
		Error::IfNegative(SDL_SetTextureBlendMode(texture, SDL_BlendMode(mode)));
	}
	LockedData Lock(const Rect& limit)
	{
        LockedData result;
        SDL_Rect rect=limit;
        Error::IfNegative(SDL_LockTexture(texture, &rect, &result.pixels, &result.bytesPerLine));
        return result;
	}
};
