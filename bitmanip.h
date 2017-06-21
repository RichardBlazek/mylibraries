#pragma once

#include "types.h"

namespace bitmanip
{
	template<typename T>
	bool GetBit(T value, uint8 index)
	{
		return (value>>index)bitand 1;
	}
	template<typename T>
	T SetBit(T value, uint8 index, bool bit)
	{
		return (value bitand(~(1<<index))) bitor(bit<<index);
	}
}