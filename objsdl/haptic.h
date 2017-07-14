#pragma once

class Haptic: public NonCopyable
{
private:
	SDL_Haptic* haptic=nullptr;
public:
	struct Direction
	{
		enum class Type: uint8
		{
			Cartesian,
			Polar,
			Spherical
		}
		Type type;
		int32 dir[3];
	};
	struct EffectBase
	{
		Direction direction;
		
		uint32 duration;
		uint16 delay;
		
		uint16 trigger_button;
		uint16 trigger_interval;
		
		uint16 attack_duration;
		uint16 force_before_attack;
		uint16 fade_duration;
		uint16 force_after_fade;
	};
	struct ConstantEffect: public EffectBase
	{		
		int16 force;
	private:
		friend Haptic;
		operator SDL_HapticEffect()const noexcept
		{
			return SDL_HapticEffect{constant: SDL_HapticConstant{SDL_HAPTIC_CONSTANT, SDL_HapticDirection{uint8(direction.type), dir}, duration, delay, trigger_button, trigger_interval, force, attack_duration, force_before_attack, fade_duration, force_after_fade}};
		}
	};
	struct PeriodEffect: public EffectBase
	{
		enum class WaveShape: uint8
		{
			Sine=SDL_HAPTIC_SINE,
			Triangle=SDL_HAPTIC_TRIANGLE,
			SawToothUp=SDL_HAPTIC_SAWTOOTHUP,
			SawToothDown=SDL_HAPTIC_SAWTOOTHDOWN
		};
		WaveShape wave_shape;
		
		uint16 period;
		int16 magnitude;
		int16 offset;
		uint16 phase;
	private:
		friend Haptic;
		operator SDL_HapticEffect()const noexcept
		{
			return SDL_HapticEffect{periodic: SDL_HapticPeriodic{uint16(wave_shape), SDL_HapticDirection{uint8(direction.type), dir}, duration, delay, trigger_button, trigger_interval, period, magnitude, offset, phase, attack_duration, force_before_attack, fade_duration, force_after_fade}};
		}
	};
	struct CustomEffect: public EffectBase
	{		
		uint8 axes;
		uint16 period;
		vector<uint16> data;
	private:
		friend Haptic;
		operator SDL_HapticEffect()const noexcept
		{
			return SDL_HapticEffect{custom: SDL_HapticCustom{SDL_HAPTIC_CUSTOM, SDL_HapticDirection{uint8(direction.type), dir}, duration, delay, trigger_button, trigger_interval, axes, period, data.size()/axes, data.data(), attack_duration, force_before_attack, fade_duration, force_after_fade}};
		}
	};
	struct RampEffect: public EffectBase
	{
		int16 start_force;
		int16 end_force;
	private:
		friend Haptic;
		operator SDL_HapticEffect()const noexcept
		{
			return SDL_HapticEffect{ramp: SDL_HapticRamp{SDL_HAPTIC_RAMP, SDL_HapticDirection{uint8(effect.direction.type), dir}, effect.duration, effect.delay, effect.trigger_button, effect.trigger_interval, effect.start, effect.end, effect.attack_duration, effect.force_before_attack, effect.fade_duration, effect.force_after_fade}};
		}	
	};
	struct ConditionEffect
	{
		enum class Type: uint16
		{
			Spring=SDL_HAPTIC_SPRING,
			Damper=SDL_HAPTIC_DAMPER,
			Inertia=SDL_HAPTIC_INERTIA,
			Friction=SDL_HAPTIC_FRICTION
		};
		Type type;
		
		uint32 duration;
		uint16 delay;
		
		uint16 trigger_button;
		uint16 trigger_interval;
		
		uint16 to_right_level;
		uint16 to_left_level;
		int16 to_right_speed;
		int16 to_left_speed;
		uint16 dead_zone_size;
		int16 dead_zone_center;
	private:
		friend Haptic;
		operator SDL_HapticEffect()const noexcept
		{
			return SDL_HapticEffect{condition: SDL_HapticCondition{uint16(type), SDL_HapticDirection{uint8(direction.type), dir}, duration, delay, trigger_button, trigger_interval, to_right_level, to_left_level, to_right_speed, to_left_speed, dead_zone_size, dead_zone_center}};
		}
	};
	struct LeftRightEffect
	{
		uint32 duration;
		
		uint16 large_motor_magnitude;
		uint16 small_motor_magnitude;
	private:
		friend Haptic;
		operator SDL_HapticEffect()const noexcept
		{
			return SDL_HapticEffect{leftright: SDL_HapticLeftRight{SDL_HAPTIC_LEFTRIGHT, length, large_motor_magnitude, small_motor_magnitude}};
		}
	};
	Haptic()=default;
	Haptic(uint32 device_index)
		:haptic(SDL_HapticOpen(device_index)) {}
	static Haptic FromMouse()
	{
		Haptic haptic;
		haptic.haptic=Error::IfZero(SDL_HapticOpenFromMouse());
		return haptic;
	}
	~Haptic()
	{
		Close();
	}
	void Close()
	{
		if(haptic)
		{
			SDL_HapticClose(haptic);
			haptic=nullptr;
		}
	}
	void Open(uint32 device_index)
	{
		auto tmp=Error::IfZero(SDL_HapticOpen(device_index));
		Close();
		haptic=tmp;
	}
	bool IsOpened()
	{
		return bool(haptic);
	}
	static bool IsOpened(uint32 device_index)
	{
		bool opened=SDL_HapticOpened(device_index);
		Error::Condition(!std::string(SDL_GetError()).empty());
		return opened;
	}
	uint32 GetIndex()
	{
		return Error::IfNegative(SDL_HapticIndex(haptic));
	}
	static std::string GetName(uint32 device_index)
	{
		return std::string(Error::IfZero(SDL_HapticIndex(device_index)));
	}
	static uint32 Count()
	{
		return Error::IfNegative(SDL_NumHaptics());
	}
	uint32 CountOfAxes()
	{
		return Error::IfNegative(SDL_HapticNumAxes(haptic));
	}
	uint32 MaxCountOfEffects()
	{
		return Error::IfNegative(SDL_HapticNumEffects(haptic));
	}
	uint32 MaxCountOfPlayingEffects()
	{
		return Error::IfNegative(SDL_HapticNumEffectsPlaying(haptic));
	}
	void InitRumble()
	{
		Error::IfNegative(SDL_HapticRumbleInit(haptic));
	}
	void PlayRumble(float force, uint32 duration)
	{
		Error::IfNegative(SDL_HapticRumblePlay(haptic, force, duration));
	}
	void StopRumble()
	{
		Error::IfNegative(SDL_HapticRumbleStop(haptic));
	}
	bool IsRumbleSupported()
	{
		return Error::IfNegative(SDL_HapticRumbleSupported(haptic))
	}
	class Effect: public NonCopyable
	{
	private:
		uint32 id;
		Effect(uint32 id):id(id){}
	public:

	};
	Effect NewEffect(ConstantEffect effect)
	{
		SDL_HapticEffect sdl=effect;
		return Effect(Error::IfNegative(SDL_HapticNewEffect(haptic, &sdl)));
	}
	Effect NewEffect(ConditionEffect effect)
	{
		SDL_HapticEffect sdl=effect;
		return Effect(Error::IfNegative(SDL_HapticNewEffect(haptic, &sdl)));
	}
	Effect NewEffect(CustomEffect effect)
	{
		SDL_HapticEffect sdl=effect;
		return Effect(Error::IfNegative(SDL_HapticNewEffect(haptic, &sdl)));
	}
	Effect NewEffect(LeftRightEffect effect)
	{
		SDL_HapticEffect sdl=effect;
		return Effect(Error::IfNegative(SDL_HapticNewEffect(haptic, &sdl)));
	}
	Effect NewEffect(PeriodEffect effect)
	{
		SDL_HapticEffect sdl=effect;
		return Effect(Error::IfNegative(SDL_HapticNewEffect(haptic, &sdl)));
	}
	Effect NewEffect(RampEffect effect)
	{
		SDL_HapticEffect sdl=effect;
		return Effect(Error::IfNegative(SDL_HapticNewEffect(haptic, &sdl)));
	}
};