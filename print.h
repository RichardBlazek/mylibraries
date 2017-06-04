#pragma once

#include <iostream>

template<typename T>
void print(const T& val)
{
	std::cout<<val;
}

template<typename T, typename... Types>
void print(const T& first, const Types&... rest)
{
	print(first);
	print(rest...);
}

template<typename... Types>
void println(const Types&... arg)
{
	print(arg...);
	print('\n');
}

template<typename T>
void debug_nonewline(const T& val)
{
	print(val, ' ');
}

template<typename T, typename... Types>
void debug_nonewline(const T& first, const Types&... rest)
{
	debug_nonewline(first);
	debug_nonewline(rest...);
}

template<typename... Types>
void debug(const Types&... arg)
{
	debug_nonewline(arg...);
	print('\n');
}