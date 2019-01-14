#pragma once

#include <string>
#include <vector>

namespace strfun
{
template<typename Char>
bool StartsWith(const std::basic_string<Char>& text, const std::basic_string<Char>& tested)
{
	return text.substr(0, tested.size())==tested;
}
template<typename Char>
bool EndsWith(const std::basic_string<Char>& text, const std::basic_string<Char>& tested)
{
	return text.substr(text.size()-tested.size())==tested;
}
template<typename Char>
std::vector<std::basic_string<Char>> Split(const std::basic_string<Char>& text, Char character)
{
    std::vector<Char> result(1);
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