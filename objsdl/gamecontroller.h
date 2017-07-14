#pragma once

class GameController
{
private:
	SDL_GameController* gcon=nullptr;
public:
	enum class Axis
	{
        Invalid=SDL_CONTROLLER_AXIS_INVALID,
        LeftX=SDL_CONTROLLER_AXIS_LEFTX,
        LeftY=SDL_CONTROLLER_AXIS_LEFTY,
        RightX=SDL_CONTROLLER_AXIS_RIGHTX,
        RightY=SDL_CONTROLLER_AXIS_RIGHTY,
        TriggerLeft=SDL_CONTROLLER_AXIS_TRIGGERLEFT,
        TriggerRight=SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
        Max=SDL_CONTROLLER_AXIS_MAX
	};
    enum class Button
    {
        Invalid=SDL_CONTROLLER_BUTTON_INVALID,
        A=SDL_CONTROLLER_BUTTON_A,
        B=SDL_CONTROLLER_BUTTON_B,
        X=SDL_CONTROLLER_BUTTON_X,
        Y=SDL_CONTROLLER_BUTTON_Y,
        Back=SDL_CONTROLLER_BUTTON_BACK,
        Guide=SDL_CONTROLLER_BUTTON_GUIDE,
        Start=SDL_CONTROLLER_BUTTON_START,
        LeftStick=SDL_CONTROLLER_BUTTON_LEFTSTICK,
        RightStick=SDL_CONTROLLER_BUTTON_RIGHTSTICK,
        LeftShoulder=SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
        RightShoulder=SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
        DPadUp=SDL_CONTROLLER_BUTTON_DPAD_UP,
        DPadDown=SDL_CONTROLLER_BUTTON_DPAD_DOWN,
        DPadLeft=SDL_CONTROLLER_BUTTON_DPAD_LEFT,
        DPadRight=SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
        Max=SDL_CONTROLLER_BUTTON_MAX
    };
    union Bind
    {
        enum class Type
        {
            None=0, Button, Axis, Hat
        };
        Type ValueType;
		struct
		{
			private:
				Type type;
			public:
				int Value;
		}Button;
		struct
		{
			private:
				Type type;
			public:
				int Value;
		}Axis;
		struct
		{
			private:
				Type type;
			public:
				int Value;
				int Mask;
		}Hat;
    };
	GameController()=default;
	void Close()
	{
		if(gcon)
		{
			SDL_GameControllerClose(gcon);
			gcon=nullptr;
		}
	}
	void Open(uint32 joy_index)
	{
		Close();
		gcon=Error::IfZero(SDL_GameControllerOpen(joy_index));
	}
    GameController(uint32 joy_index)
    {
		Open(joy_index);
    }
    ~GameController()
    {
        Close();
    }
    bool IsOpened()const
    {
    	return bool(gcon);
    }
    static void Update()
    {
		SDL_GameControllerUpdate();
    }
    std::string GetName()
    {
        auto str=SDL_GameControllerName(gcon);
        return std::string(str?str:"");
    }
    static std::string NameOf(uint32 joy_index)
    {
		auto str=SDL_GameControllerNameForIndex(joy_index);
        return std::string(str?str:"");
    }
    static void EnableEventPolling()
	{
		Error::Condition(SDL_GameControllerEventState(1)<0);
	}
    static void DisableEventPolling()
	{
		Error::Condition(SDL_GameControllerEventState(0)<0);
	}
    static bool IsEnabledEventPolling()
	{
		return Error::IfNegative(SDL_GameControllerEventState(-1));
	}
	static std::string FormatMapping(const Joystick::GUID& guid, const std::string& name, const std::string& mapping)
	{
		return std::string((const char*)guid.data, 16)+","+name+","+mapping;
	}
	static std::tuple<Joystick::GUID, std::string, std::string> ScanMapping(const std::string& mappingtext)
	{
		std::tuple<Joystick::GUID, std::string, std::string> result;
		bool wascomma=false;
		for(size_t i=0;i<mappingtext.size();++i)
		{
            if(mappingtext[i]==',')
			{
                if(!wascomma)
				{
					memcpy(std::get<0>(result).data, mappingtext.c_str(), 16);
					wascomma=true;
				}
				else
				{
                    std::get<1>(result)=mappingtext.substr(16, i-16);
                    std::get<2>(result)=mappingtext.substr(i, mappingtext.size()-i);
                    return result;
				}
			}
		}
		throw Error("GameController::ScanMapping(mappingtext)where mappingtext="+mappingtext+">invalid format of mappingtext");
	}
	///Returns true if added, false if updated
	static bool AddMapping(const std::string& mappingtext)
	{
		return Error::IfNegative(SDL_GameControllerAddMapping(mappingtext.c_str()));
	}
	std::string GetMapping()
	{
		char* mappingstr=Error::IfZero(SDL_GameControllerMapping(gcon));
		std::string mappingtext=mappingstr;
		SDL_free(mappingstr);
        return mappingtext;
	}
	static std::string GetMappingForGUID(const Joystick::GUID& guid)
	{
        char* mappingstr=Error::IfZero(SDL_GameControllerMappingForGUID(guid));
		std::string mappingtext=mappingstr;
		SDL_free(mappingstr);
        return mappingtext;
	}
	bool IsAttached()
	{
        return SDL_GameControllerGetAttached(gcon);
	}
	int16 GetAxis(Axis axis)
	{
		int16 value=SDL_GameControllerGetAxis(gcon, sdlAxis(axis));
		Error::Condition(value==0&&!std::string(SDL_GetError()).empty());
		return value;
	}
	bool GetButton(Button button)
	{
		bool value=SDL_GameControllerGetButton(gcon, sdlButton(button));
		Error::Condition(!value&&!std::string(SDL_GetError()).empty());
		return value;
	}
	static Axis AxisFromString(const std::string& str)
	{
        return Axis(SDL_GameControllerGetAxisFromString(str.c_str()));
	}
	static Button ButtonFromString(const std::string& str)
	{
        return Button(SDL_GameControllerGetButtonFromString(str.c_str()));
	}
	static std::string StringFromAxis(Axis axis)
	{
		auto str=SDL_GameControllerGetStringForAxis(sdlAxis(axis));
        return std::string(str?str:"");
	}
	static std::string StringFromButton(Button button)
	{
		auto str=SDL_GameControllerGetStringForButton(sdlButton(button));
        return std::string(str?str:"");
	}
	Bind GetBindForAxis(Axis axis)
	{
        auto bind=SDL_GameControllerGetBindForAxis(gcon, sdlAxis(axis));
        Bind result;
        result.ValueType=Bind::Type(bind.bindType);
        if(result.ValueType==Bind::Type::Axis)
		{
			result.Axis.Value=bind.value.axis;
		}
        else if(result.ValueType==Bind::Type::Button)
		{
			result.Button.Value=bind.value.button;
		}
        else if(result.ValueType==Bind::Type::Hat)
		{
			result.Hat.Value=bind.value.hat.hat;
			result.Hat.Mask=bind.value.hat.hat_mask;
		}
		return result;
	}
	Bind GetBindForButton(Button button)
	{
        auto bind=SDL_GameControllerGetBindForButton(gcon, sdlButton(button));
        Bind result;
        result.ValueType=Bind::Type(bind.bindType);
        if(result.ValueType==Bind::Type::Axis)
		{
			result.Axis.Value=bind.value.axis;
		}
        else if(result.ValueType==Bind::Type::Button)
		{
			result.Button.Value=bind.value.button;
		}
        else if(result.ValueType==Bind::Type::Hat)
		{
			result.Hat.Value=bind.value.hat.hat;
			result.Hat.Mask=bind.value.hat.hat_mask;
		}
		return result;
	}
};
bool IsGameController(uint32 joy_index)
{
    return bool(SDL_IsGameController(joy_index));
}