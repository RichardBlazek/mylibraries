#pragma once

#include "types.h"

namespace func
{
///Pretypovani na r-hodnotu
template<typename T>inline constexpr
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
size_t Size(T(&)[S])
{
	return S;
}
template<typename T>constexpr
size_t Size(T& x)
{
	return x.size();
}

template<typename T, typename T2>inline constexpr
T Max(const T& arg1, const T2& arg2)
{
    return (arg1>arg2)?arg1:arg2;
}

template<typename T, typename T2, typename... types>inline constexpr
T Max(const T& arg1, const T2& arg2, const types&... args)
{
    return Max(Max(arg1, arg2), args...);
}

template<typename T, typename T2>inline constexpr
T Min(const T& arg1, const T2& arg2)
{
    return (arg1<arg2)?arg1:arg2;
}

template<typename T, typename T2, typename... types>inline constexpr
T Min(const T& arg1, const T2& arg2, const types&... args)
{
    return Min(Min(arg1, arg2), args...);
}

template<typename T>inline constexpr
T Limit(T x, T min, T max)
{
    return func::Min(func::Max(x, min), max);
}
template<typename T, typename T2>inline constexpr
bool Ordered(const T& arg1, const T2& arg2)
{
    return arg1<arg2;
}

template<typename T, typename T2, typename... types>inline constexpr
bool Ordered(const T& arg1, const T2& arg2, const types&... args)
{
    return Ordered(arg1, arg2)&&Ordered(arg2, args...);
}
template<typename T, typename T2>inline constexpr
auto Sum(const T& arg1, const T2& arg2)
{
    return arg1+arg2;
}

template<typename T, typename... Types>inline constexpr
auto Sum(const T& arg1, const Types&... args)
{
    return arg1+Sum<Types...>(args...);
}

template<typename... T>inline constexpr
auto Avg(const T&... arg)
{
    return Sum<T...>(arg...)/sizeof...(arg);
}


template<typename Pair, typename ContA, typename ContB, typename Func>constexpr
Pair BestPair(const ContA& list_a, const ContB& list_b, Func better)
{
    Pair best{list_a.begin(), list_b.begin()};
    for(auto& a:list_a)
    {
        for(auto& b:list_b)
        {
            best=better(best, {&a, &b});
        }
    }
    return best;
}
}