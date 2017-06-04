#pragma once

#include <initializer_list>

#include "dynarr.h"
#include "func.h"

namespace containers
{
template<typename value_t, typename index_t>
class Map
{
public:
    struct value_type
    {
    	value_t value;
    	index_t index;
    };
private:
	containers::DynArr<value_type> array;
public:
	Map()=default;
	~Map()=default;
	Map(std::initializer_list<value_type> init)
			:array(init){}
	Map(Map&& init):array(func::Move(init.array)){}
	Map& operator=(Map&& init)
	{
		array=func::Move(init.array);
	}
	inline std::size_t size()const
	{
		return array.size();
	}
	containers::DynArr<value_type> data()const
	{
		return array;
	}
	value_t& operator[](index_t index)
	{
		for(auto& x:array)
		{
            if(x.index==index)
				return x.value;
		}
		array.push_back({value_t(), index});
		return array.back().value;
	}
	Map& remove(index_t index)
	{
		for(std::size_t i=0;i<size()-1;++i)
		{
			if(array[i].index==index)
			{
				func::Swap(array[i],array[i+1]);
			}
		}
		array.pop_back();
		return *this;
	}
};
}