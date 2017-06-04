#pragma once

#include <tuple>
#include <string>
#include <cmath>
#include <cstdlib>
#include "dynarr.h"
#include "types.h"

#include "oldsdl.h"

///Object wrapper for SDL
namespace SDL
{
#include "shapes.h"
#include "color.h"
#include "sdl_base.h"
#include "decl.h"
#include "wm.h"
#include "time.h"
#include "gamecontroller.h"
#include "event.h"
#include "keyboard.h"
#include "window.h"
#include "surface.h"
#include "renderer.h"
#include "cursor.h"
#include "audio.h"
#include "messagebox.h"
#include "joystick.h"
#include "powerstate.h"
#include "clipboard.h"
#include "screensaver.h"
#include "textinput.h"
}