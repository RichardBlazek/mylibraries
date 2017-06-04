#pragma once

class Palette
{
private:
	SDL_Palette* palette;
public:
	void Destroy()
	{
		if(palette)
		{
			SDL_FreePalette(palette);
			palette=nullptr;
		}
	}
	void Create(size_t size)
	{
		Destroy();
		palette=SDL_AllocPalette(size);
		if(!palette)
			throw Error();
	}
    inline size_t size()const
    {
    	return palette->ncolors;
    }
    Palette():palette(nullptr){}
    Palette(size_t size)
    {
    	Create(size);
    }
    Palette(const Palette& init):Palette(init.size())
    {
    	for(size_t i=0;i<size();++i)
		{
			palette->colors[i]=init[i];
		}
    }
    Palette(Palette&& init):palette(init.palette)
    {
    	init.palette=nullptr;
    }
    Palette& operator=(const Palette& init)
    {
		Create(init.size());
		for(size_t i=0;i<size();++i)
		{
			palette->colors[i]=init[i];
		}
		return *this;
    }
    Palette& operator=(Palette&& init)
    {
    	Destroy();
    	palette=init.palette;
    	init.palette=nullptr;
    	return *this;
    }
    ~Palette()
    {
    	Destroy();
    }
	Color& operator[](size_t i)const
	{
		if(i>=size())
			throw Error("Palette index overflow");
		return palette->colors[i];
	}
	void SetColors(Color* colors, size_t first, size_t count)const
	{
        Error::Condition(SDL_SetPaletteColors(palette, colors, first, count)<0);
	}
};
