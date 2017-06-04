#pragma once

#include <string>
#include <windows.h>

#include "types.h"
#include <cstdlib>

class console
{
private:
	static uint8 BGcol, FGcol;
public:
	console()=delete;
    static inline void SetColor(uint8 background, uint8 foreground)noexcept
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (BGcol=background)*16+ (FGcol=foreground));
    }
    static inline void SetBGcol(uint8 background)noexcept
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (BGcol=background)*16+FGcol);
    }
    static inline void SetFGcol(uint8 foreground)noexcept
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BGcol*16+ (FGcol=foreground));
    }
    static inline void Clear()noexcept
    {
        system("cls");
    }
    static inline void SetTitle(std::string txt)noexcept
	{
		SetConsoleTitleA(txt.c_str());
	}
	static inline void SetTitle(std::wstring txt)noexcept
	{
		SetConsoleTitleW(txt.c_str());
	}
};
uint8 console::BGcol=0, console::FGcol=7;
inline void Wait(uint32 ms)noexcept
{
	Sleep(ms);
}

namespace cursor
{
	inline void Show()noexcept
    {
        CONSOLE_CURSOR_INFO info{100, true};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    }
    inline void Hide()noexcept
    {
        CONSOLE_CURSOR_INFO info{100, false};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    }
    inline void Move(int16 x, int16 y)noexcept
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {x, y} );
    }
}