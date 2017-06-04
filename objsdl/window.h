#pragma once

Window::Window(const std::string& title, int x, int y, int widht, int height, Flags flags)
					:window(SDL_CreateWindow(title.c_str(),x,y,widht,height,uint32(flags)))
{
	Error::IfZero(window);
}
void Window::Close()noexcept
{
	if(window)
	{
		SDL_DestroyWindow(window);
		window=nullptr;
	}
}
Window::Window(Window&& init)noexcept:window(init.window)
{
	init.window=nullptr;
}
Window& Window::operator=(Window&& init)noexcept
{
	Close();
	window=init.window;
	init.window=nullptr;
	return *this;
}
///If was Window destroyed, this function open them again
///If not, function destroy the window and open them again
void Window::Open(std::string title, int x, int y, int widht, int height, uint32 flags)
{
    Close();
    window=SDL_CreateWindow(title.c_str(),x,y,widht,height,flags);
    Error::IfZero(window);
}
void Window::SetIcon(Surface& image)noexcept
{
	SDL_SetWindowIcon(window, image.surface);
}