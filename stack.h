#pragma once

#include "func.h"
#include "dynarr.h"

namespace containres
{
template<typename typ>
class Stack
{
private:
	containers::DynArr<typ> array;
public:
    ///Normální konstruktor
    Stack():array(0){}
    Stack(const Stack& vzor)
			:array(vzor.array){}
    Stack(Stack&& zdroj)
			:array(func::Move(zdroj.array)){}
	Stack(std::initializer_list<typ> init)
			:array(init){}
    inline size_t size()const
    {
        return array.size();
    }
    inline typ* begin()const noexcept
    {
        return array.begin();
    }
    inline typ* end()const noexcept
    {
        return array.end();
    }
    inline bool empty()const noexcept
    {
        return array.size()==1;
    }
    inline containers::DynArr<typ>& data()
    {
    	return array;
    }
    Stack& operator=(const Stack& vzor)
    {
    	array=vzor.array;
        return *this;
    }
    Stack& push(typ value)
    {
        array.push_back(value);
        return *this;
    }
    Stack& pop()
    {
    	array.pop_back();
        return *this;
    }
    inline typ& top()const
    {
        return array.back();
    }
};
}