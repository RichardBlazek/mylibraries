#pragma once

#include "objsdl.h"
#include "nocopy.h"

namespace gui
{
	SDL::Font font;
	void Init(std::string file, uint32 size=12)
	{
		SDL::Init();
		font.Open(file, size);
	}
	#include "gui/widget.h"
	#include "gui/label.h"
	#include "gui/button.h"
	#include "gui/chars.h"
	#include "gui/textinputbox.h"
	#include "gui/dialog.h"
}