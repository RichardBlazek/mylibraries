#pragma once

#include <string>
#include "dynarr.h"

namespace strfun
{
template<typename Char>
using String=std::basic_string<Char>;

template<typename Char>
using StringList=containers::DynArr<String<Char>>;

template<typename Char>
StringList<Char> Split(const String<Char>& text, Char character)
{
    StringList<Char> result(1);
    for(auto& c:text)
	{
        if(c==character)
		{
			result.increase_size(1);
		}
		else
		{
			result.back()+=c;
		}
	}
	return func::Move(result);
}
}