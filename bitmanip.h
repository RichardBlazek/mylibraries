#pragma once

#include "types.h"

namespace bitmanip
{
	bool GetBit(uint8 value, uint8 index)
	{
		return (value>>index)bitand 1;
	}
	uint8 SetBit(uint8 value, uint8 index, bool setvalue)
	{
		return (value bitand(~(1<<index))) bitor(setvalue<<index);
	}
	bool GetBit(int8 value, uint8 index)
	{
		return (value>>index)bitand 1;
	}
	int8 SetBit(int8 value, uint8 index, bool setvalue)
	{
		return (value bitand(~(1<<index))) bitor(setvalue<<index);
	}
	bool GetBit(uint16 value, uint8 index)
	{
		return (value>>index)bitand 1;
	}
	uint16 SetBit(uint16 value, uint8 index, bool setvalue)
	{
		return (value bitand(~(1<<index))) bitor(setvalue<<index);
	}
	bool GetBit(int16 value, uint8 index)
	{
		return (value>>index)bitand 1;
	}
	int16 SetBit(int16 value, uint8 index, bool setvalue)
	{
		return (value bitand(~(1<<index))) bitor(setvalue<<index);
	}
	bool GetBit(uint32 value, uint8 index)
	{
		return (value>>index)bitand 1;
	}
	uint32 SetBit(uint32 value, uint8 index, bool setvalue)
	{
		return (value bitand(~(1<<index))) bitor(setvalue<<index);
	}
	bool GetBit(int32 value, uint8 index)
	{
		return (value>>index)bitand 1;
	}
	int32 SetBit(int32 value, uint8 index, bool setvalue)
	{
		return (value bitand(~(1<<index))) bitor(setvalue<<index);
	}
	bool GetBit(uint64 value, uint8 index)
	{
		return (value>>index)bitand 1;
	}
	uint64 SetBit(uint64 value, uint8 index, bool setvalue)
	{
		return (value bitand(~(1<<index))) bitor(setvalue<<index);
	}
	bool GetBit(int64 value, uint8 index)
	{
		return (value>>index)bitand 1;
	}
	int64 SetBit(int64 value, uint8 index, bool setvalue)
	{
		return (value bitand(~(1<<index))) bitor(setvalue<<index);
	}
}