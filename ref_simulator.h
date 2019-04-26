#pragma once

#include <functional>

template<typename T>
class RefSimulator
{
private:
	std::function<T()> get;
	std::function<void(T)> set;
public:
	RefSimulator(std::function<T()> get, std::function<void(T)> set):get(get), set(set) {}
	RefSimulator& operator=(const RefSimulator& another)
	{
		set(another.get());
		return *this;
	}
	RefSimulator& operator=(const T& new_value)
	{
		set(new_value);
		return *this;
	}
	operator T()const
	{
		return std::move(get());
	}
};