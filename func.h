#pragma once

#include "types.h"

namespace func
{
///Pretypovani na r-hodnotu
template<typename T>inline
T&& Move(const T& obj)
{
    return (T&&)obj;
}

///Prohozeni 2 hodnot
template<typename T>
void Swap(T& a, T& b)
{
    T tmp(Move(a));
    a=Move(b);
    b=Move(tmp);
}

template<typename T, size_t S>constexpr
size_t ArraySize(T(&)[S])
{
	return S;
}
template<typename T>constexpr
size_t ArraySize(T& x)
{
	return x.size();
}

template<typename T, typename T2>inline
const T& Max(const T& arg1, const T2& arg2)
{
    return (arg1>arg2)?arg1:arg2;
}

template<typename T, typename T2, typename... types>inline
const T& Max(const T& arg1, const T2& arg2, const types&... args)
{
    return Max(Max(arg1, arg2), args...);
}

template<typename T, typename T2>inline
const T& Min(const T& arg1, const T2& arg2)
{
    return (arg1<arg2)?arg1:arg2;
}

template<typename T, typename T2, typename... types>inline
const T& Min(const T& arg1, const T2& arg2, const types&... args)
{
    return Min(Min(arg1, arg2), args...);
}

template<typename T>
T Limit(T x, T min, T max)
{
    return func::Min(func::Max(x, min), max);
}
template<typename T, typename T2>inline
bool Ordered(const T& arg1, const T2& arg2)
{
    return arg1<arg2;
}

template<typename T, typename T2, typename... types>inline
bool Ordered(const T& arg1, const T2& arg2, const types&... args)
{
    return Ordered(arg1, arg2)&&Ordered(arg2, args...);
}
template<typename T, typename T2>inline
auto Sum(const T& arg1, const T2& arg2)
{
    return arg1+arg2;
}

template<typename T, typename... Types>inline
T Sum(const T& arg1, const Types&... args)
{
    return arg1+Sum(args...);
}

template<typename... T>inline
auto Avg(const T&... arg)
{
    return Sum(arg...)/sizeof...(arg);
}
}