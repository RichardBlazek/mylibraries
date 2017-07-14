#pragma once

enum class SystemCursor
{
	Arrow,Ibeam,Wait,Crosshair,WaitArrow,SizeNWSE,
	SizeNESW,SizeWE,SizeNS,SizeAll,No,Hand
};

class Cursor: public NonCopyable
{
private:
	SDL_Cursor* cursor=nullptr;
public:
	Cursor()=default;
	Cursor(Cursor&& init):cursor(init.cursor)
	{
		init.cursor=nullptr;
	}
	Cursor& operator=(Cursor&& init)
	{
		cursor=init.cursor;
		init.cursor=nullptr;
		return *this;
	}
	Cursor(const uint8* data, const uint8* mask, uint32 height, uint32 widht, uint32 hot_x, uint32 hot_y)
			:cursor(SDL_CreateCursor(data,mask,height,widht,hot_x,hot_y))
	{
		Error::IfZero(cursor);
	}
	explicit Cursor(SystemCursor id)
		:cursor(SDL_CreateSystemCursor(SDL_SystemCursor(id)))
	{
		Error::IfZero(cursor);
	}
	explicit Cursor(Surface& image, Point active={0,0})
		:cursor(SDL_CreateColorCursor(image.surface, active.x, active.y))
	{
		Error::IfZero(cursor);
	}
	~Cursor()noexcept
	{
		if(cursor)
		{
			SDL_FreeCursor(cursor);
			cursor=nullptr;
		}
	}
    //Schová kurzor
	static void Hide()noexcept
	{
		SDL_ShowCursor(0);
	}
	///Zobrazí kurzor
	static void Show()noexcept
	{
		SDL_ShowCursor(1);
	}
	//Je kurzor vidět?
	static bool IsVisible()noexcept
	{
		return SDL_ShowCursor(-1);
	}
    static void Move(Window& window, Point xy)noexcept
	{
		SDL_WarpMouseInWindow(window.window, xy.x, xy.y);
	}
	static void Move(Point xy)noexcept
	{
        Error::Condition(SDL_WarpMouseGlobal(xy.x, xy.y)<0);
	}
	static void EnableCapturing()
	{
		Error::Condition(SDL_CaptureMouse(SDL_TRUE)<0);
	}
	static void DisableCapturing()
	{
		Error::Condition(SDL_CaptureMouse(SDL_FALSE)<0);
	}
	static Point Position()
	{
		Point result;
		SDL_GetMouseState(&result.x, &result.y);
		return result;
	}
	static Point GlobalPosition()
	{
		Point result;
		SDL_GetGlobalMouseState(&result.x, &result.y);
		return result;
	}
	static Point RelativePosition()
	{
		Point result;
		SDL_GetRelativeMouseState(&result.x, &result.y);
		return result;
	}
	static MouseButtonMask PressedButtons()
	{
		return MouseButtonMask(SDL_GetMouseState(0,0));
	}
	static bool IsPressed()
	{
		return PressedButtons()!=MouseButtonMask::None;
	}
};