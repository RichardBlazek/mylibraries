#pragma once

#include <vector>
#include "func.h"

namespace strfun
{
template<typename String>
bool StartsWith(const String& text, const String& tested)
{
	return text.substr(0, tested.size())==tested;
}
template<typename String>
bool EndsWith(const String& text, const String& tested)
{
	return text.substr(text.size()-tested.size())==tested;
}
template<typename String, typename Char>
std::vector<String> Split(const String& text, Char character)
{
    std::vector<String> result(1);
    for(auto& c:text)
	{
        if(c==character)
		{
			result.push_back("");
		}
		else
		{
			result.back()+=c;
		}
	}
	return func::Move(result);
}
}