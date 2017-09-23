#pragma once

#include <string>
#include <windows.h>

#include "types.h"
#include <cstdlib>

namespace console
{
    inline void SetColor(uint8 background, uint8 foreground)noexcept
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (BGcol=background)*16+ (FGcol=foreground));
    }
    inline void Clear()noexcept
    {
        system("cls");
    }
    inline void SetTitle(std::string txt)noexcept
	{
		SetConsoleTitleA(txt.c_str());
	}
	inline void SetTitle(std::wstring txt)noexcept
	{
		SetConsoleTitleW(txt.c_str());
	}
	inline void Hide()noexcept
	{
		HWND wind;
		AllocConsole();
		wind=FindWindowA("ConsoleWindowclass", nullptr);
		ShowWindow(wind, 0);
	}
	inline void Show()noexcept
	{
		HWND wind;
		AllocConsole();
		wind=FindWindowA("ConsoleWindowclass", nullptr);
		ShowWindow(wind, 1);
	}
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