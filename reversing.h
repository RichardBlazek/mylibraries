#pragma once

namespace containers
{
template<typename iter>class IteratorPair
{
private:
	iter first, last;
public:
	IteratorPair(const iter& begin, const iter& last):first(begin), last(last) {}
	iter begin()
	{
		return first;
	}
	iter end()
	{
		return last;
	}
};
template<typename T>
auto Reverse(T& container)
{
	return IteratorPair<decltype(container.rbegin())>(container.rbegin(),container.rend());
}
template<typename T>
auto Reverse(const T& container)
{
	return IteratorPair<decltype(container.rbegin())>(container.rbegin(),container.rend());
}
template<typename T, size_t len>
auto Reverse(T(&array)[len])
{
	return IteratorPair<std::reverse_iterator<T*>>(std::reverse_iterator<T*>(array+len), std::reverse_iterator<T*>(array));
}
}