#pragma once

#include <cstdint>

using int8=std::int8_t;
using int16=std::int16_t;
using int32=std::int32_t;
using int64=std::int64_t;
using uint8=std::uint8_t;
using uint16=std::uint16_t;
using uint32=std::uint32_t;
using uint64=std::uint64_t;
using size_t=std::uintptr_t;
using ptrdiff_t=std::intptr_t;

template<typename Res, typename... Args>
using FunctionPtr=Res(*)(Args...);

template<typename Res, typename... Args>
using FunctionRef=Res(&)(Args...);

template<typename Class, typename Res, typename... Args>
using MethodPtr=Res(Class::*)(Args...);

template<typename Class, typename Res, typename... Args>
using ConstMethodPtr=Res(Class::*)(Args...)const;

template<typename Class, typename T, typename... Args>
inline auto Invoke(Class obj, T method, Args... args)
{
	return (obj.*method)(args...);
}