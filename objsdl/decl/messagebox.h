#pragma once

namespace MessageBox
{

enum class Flags : uint32
{
	None=0,
    Error=SDL_MESSAGEBOX_ERROR,
    Warning=SDL_MESSAGEBOX_WARNING,
    Info=SDL_MESSAGEBOX_INFORMATION
};

using ColorScheme=SDL_MessageBoxColorScheme;

void Show(const std::string& title, const std::string& message, Flags flag=Flags::None, SDL::Window* window=nullptr);
std::string Dialog(const std::string& title, const std::string& message, const containers::DynArr<std::string>& buttons, size_t DefaultReturnkey=0, size_t DefaultEscapekey=0, Flags flag=Flags::None, ColorScheme* color=nullptr, Window* window=nullptr);
}