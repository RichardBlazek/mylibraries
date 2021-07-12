#pragma once

class NonCopyable
{
public:
	constexpr NonCopyable(){}
	NonCopyable(const NonCopyable&)=delete;
	NonCopyable& operator=(const NonCopyable&)=delete;
};