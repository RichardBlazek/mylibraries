#pragma once

void Wait(uint32 miliseconds)noexcept
{
    SDL_Delay(miliseconds);
}
uint32 RunTimeMs()noexcept
{
    return SDL_GetTicks();
}
uint64 RunTimeTicks()noexcept
{
    return SDL_GetPerformanceCounter();
}
uint64 TicksPerSec()noexcept
{
    return SDL_GetPerformanceFrequency();
}
using TimerCallback=SDL_TimerCallback;//uint32(*)(uint32,void*)
int AddTimer(uint32 interval, TimerCallback callback, void* param)
{
	interval=SDL_AddTimer(interval, callback, param);
	Error::IfZero(interval);
    return interval;
}
void RemoveTimer(int ID)
{
    Error::IfZero(SDL_RemoveTimer(ID));
}