#pragma once

Joystick::Joystick():joystick(nullptr){}
Joystick::Joystick(Joystick&& joy):joystick(joy.joystick)
{
	joy.joystick=nullptr;
}
Joystick& Joystick::operator=(Joystick&& joy)
{
	joystick=joy.joystick;
	joy.joystick=nullptr;
	return *this;
}
void Joystick::Close()
{
	if(IsOpened())
	{
		SDL_JoystickClose(joystick);
		joystick=nullptr;
	}
}
void Joystick::Open(int device_index)
{
	Close();
	joystick=SDL_JoystickOpen(device_index);
	Error::Condition(!joystick);
}
Joystick::Joystick(int device_index)
{
    joystick=SDL_JoystickOpen(device_index);
	Error::Condition(!joystick);
}
Joystick::~Joystick()
{
	Close();
}
std::string Joystick::Name()
{
	const char* tmp=SDL_JoystickName(joystick);
	Error::Condition(!tmp);
	return tmp;
}
std::string Joystick::NameFromIndex(int device_index)
{
	const char* tmp=SDL_JoystickNameForIndex(device_index);
	Error::Condition(!tmp);
	return tmp;
}
uint32 Joystick::GetId()
{
	int tmp=SDL_JoystickInstanceID(joystick);
	Error::Condition(tmp<0);
	return tmp;
}
uint32 Joystick::NumAxes()
{
	int tmp=SDL_JoystickNumAxes(joystick);
	Error::Condition(tmp<0);
	return tmp;
}
uint32 Joystick::NumBalls()
{
	int tmp=SDL_JoystickNumBalls(joystick);
	Error::Condition(tmp<0);
	return tmp;
}
uint32 Joystick::NumButtons()
{
	int tmp=SDL_JoystickNumButtons(joystick);
	Error::Condition(tmp<0);
	return tmp;
}
uint32 Joystick::NumHats()
{
	int tmp=SDL_JoystickNumHats(joystick);
	Error::Condition(tmp<0);
	return tmp;
}
void Joystick::Update()
{
	SDL_JoystickUpdate();
}
uint32 Joystick::Num()
{
	int tmp=SDL_NumJoysticks();
	Error::Condition(tmp<0);
	return tmp;
}
int16 Joystick::GetAxis(int axis)
{
	int16 value=SDL_JoystickGetAxis(joystick, axis);
	Error::Condition(value==0&&std::string(SDL_GetError())!="");
	return value;
}
Point Joystick::GetBallPos(int ball)
{
	Point dot;
	Error::Condition(SDL_JoystickGetBall(joystick, ball, &dot.x, &dot.y)<0);
	return dot;
}
bool Joystick::IsPressed(int button)
{
	return SDL_JoystickGetButton(joystick, button);
}
auto Joystick::GetHatState(int hat)->HatState
{
	return HatState(SDL_JoystickGetHat(joystick,hat));
}
void Joystick::EnableEventPolling()
{
	Error::Condition(SDL_JoystickEventState(1)<0);
}
void Joystick::DisableEventPolling()
{
	Error::Condition(SDL_JoystickEventState(0)<0);
}
bool Joystick::IsEnabledEventPolling()
{
	return Error::IfNegative(SDL_JoystickEventState(-1));
}
bool Joystick::IsAttached()
{
	return SDL_JoystickGetAttached(joystick);
}
auto Joystick::GetGUID()->GUID
{
	GUID tmp=SDL_JoystickGetGUID(joystick);
	bool zero=true;
	for(auto& element:tmp.data)
	{
		if(element)
		{
			zero=false;
		}
	}
	Error::Condition(zero);
	return tmp;
}
std::string Joystick::GUID_ToString(GUID guid)
{
	char tmp[65]={0};
	SDL_JoystickGetGUIDString(guid, tmp, 64);
	return std::string(tmp);
}
auto Joystick::GUID_FromString(std::string str)->GUID
{
	return SDL_JoystickGetGUIDFromString(str.c_str());
}