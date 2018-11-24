#pragma once

#include "types.h"

namespace bitmanip
{
	template<typename T>
	T GetBits(T value, uint8 index, uint8 bit_count)
	{
		return (value>>index)&(1<<bit_count-1)
	}
	template<typename T>
	T SetBits(T value, uint8 index, T bits, uint8 bit_count)
	{
		return (value&(~((1<<bit_count-1)<<index)))|(bit<<index);
	}
	template<typename T>
	bool GetBit(T value, uint8 index)
	{
		return GetBits(value, index, 1);
	}
	template<typename T>
	T SetBit(T value, uint8 index, bool bit)
	{
		return SetBits(value, index, 1, bits);
	}
}