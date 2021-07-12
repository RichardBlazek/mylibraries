#pragma once

#include <vector>
#include <string>
#include <utility>

template<typename CharT>
bool StartsWith(const std::basic_string<CharT>& text, const String& tested)
{
	return text.substr(0, tested.size())==tested;
}
template<typename CharT>
bool EndsWith(const std::basic_string<CharT>& text, const String& tested)
{
	return text.substr(text.size()-tested.size())==tested;
}
template<typename CharT>
void Split(const std::basic_string<CharT>& str, char sep, bool trim_empty=false)
{
	vector<std::basic_string<CharT>> tokens;
	size_t pos=0, last_pos=0, length=str.size();
	while(last_pos<length+1)
	{
		pos=str.find(sep, last_pos);
		if(pos==std::string::npos)
		{
			pos=length;
		}
		if(pos!=last_pos||!trim_empty)
		{
			tokens.push_back(basic_string<CharT>(str.data()+last_pos, pos-last_pos));
		}
		last_pos=pos+1;
	}
}