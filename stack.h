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
    Stack()=default;
	Stack(std::initializer_list<typ> init)
			:array(init){}
    Stack(Stack&& zdroj)
			:array(func::Move(zdroj.array)){}
    Stack& operator=(Stack&& vzor)
    {
    	array=func::Move(vzor.array);
        return *this;
    }
    size_t size()const
    {
        return array.size();
    }
    auto begin()const noexcept
    {
        return array.rbegin();
    }
    auto end()const noexcept
    {
        return array.rend();
    }
    bool empty()const noexcept
    {
        return array.size()==0;
    }
    containers::DynArr<typ>& data()
    {
    	return array;
    }
    typ& top()const
    {
        return array.back();
    }
    void push(typ value)
    {
        array.push_back(value);
        return *this;
    }
    typ& pop()
    {
        auto x=top();
    	array.pop_back();
        return x;
    }
};
}