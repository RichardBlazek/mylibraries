#pragma once

#include "objsdl.h"

namespace gui
{
	SDL::Font font;
	void Init(std::string file)
	{
		SDL::Init();
		font.Open(file, 12);
	}
	#include "gui/button.h"
	bool IsASCII(char c)
	{
		return uint8(c)<0x80;
	}
	bool IsMultibyteStart(char c)
	{
		return !IsASCII(c)&&uint8(c)<=0xBF;
	}
	bool IsMultibyteByte(char c)
	{
		return uint8(c)>=0xC0&&uint8(c)<=0xFD;
	}
	#include "gui/textinputbox.h"
}