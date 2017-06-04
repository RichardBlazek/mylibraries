#pragma once

#include <initializer_list>
#include <iterator>
#include <exception>
#include "types.h"
#include "func.h"

namespace containers
{
template<typename typ>
class DynArr
{
private:
	typ* alloc;
	size_t len;
	size_t cap;
public:
	using iterator=typ*;
	using reverse_iterator=std::reverse_iterator<typ*>;
	DynArr():alloc(new typ[0]),len(0),cap(0) {}
	explicit DynArr(size_t siz):alloc(new typ[siz]),len(siz),cap(siz) {}
	DynArr(const std::initializer_list<typ>& init):DynArr(init.size())
	{
		std::copy(init.begin(),init.end(), alloc);
	}
	DynArr(std::initializer_list<typ>&& init):DynArr(init.size())
	{
		size_t i=0;
		for(auto& x:init)
		{
            alloc[i]=func::Move(x);
            ++i;
		}
	}
	~DynArr()
	{
		delete[]alloc;
	}
	DynArr(const DynArr& init):DynArr(init.len)
	{
		std::copy(init.begin(), init.end(), alloc);
	}
	DynArr(DynArr&& init)noexcept :alloc(init.alloc),len(init.len),cap(init.cap)
	{
		init.alloc=nullptr;
		init.len=0;
		init.cap=0;
	}
	DynArr& operator=(const DynArr& vct)
	{
		delete[] alloc;
		cap=len=vct.len;
		alloc=new typ[cap];
		std::copy(vct.alloc, vct.alloc+len, alloc);
		return *this;
	}
	DynArr& operator=(DynArr&& vct)noexcept
	{
		delete[]alloc;
		alloc=vct.alloc;
		len=vct.len;
		cap=vct.cap;
		vct.alloc=nullptr;
		vct.len=0;
		vct.cap=0;
		return *this;
	}
	size_t size()const noexcept
	{
		return len;
	}
	typ& operator[](size_t index)const
	{
		if(index<len)
		{
			return alloc[index];
		}
		else
		{
			throw std::out_of_range("DynArr::operator[] index:"+std::to_string(index)+" lenght:"+std::to_string(len));
		}
	}
	iterator begin()const noexcept
	{
		return alloc;
	}
	iterator end()const noexcept
	{
		return alloc+len;
	}
	reverse_iterator rbegin()const noexcept
	{
		return reverse_iterator(alloc+len);
	}
	reverse_iterator rend()const noexcept
	{
		return reverse_iterator(alloc);
	}
	void reduce()
	{
		DynArr tmp=func::Move(*this);
		cap=len=tmp.len;
		alloc=new typ[cap];
		std::move(tmp.alloc, tmp.alloc+cap, alloc);
	}
	void fill(const typ& value)noexcept
	{
		std::fill(alloc, alloc+len, value);
	}
	bool empty()const noexcept
	{
		return len==0;
	}
	typ& back()const
	{
		if(empty())
		{
			throw std::out_of_range("DynArr is empty!");
		}
		return alloc[len-1];
	}
	void clear()
	{
		delete[]alloc;
		cap=len=0;
		alloc=new typ[0];
	}
	void resize(size_t size)
	{
		if(size<=cap)
		{
			len=size;
			if(size<=(cap>>2))
			{
				reduce();
			}
		}
		else if(size<=cap*2)
		{
			DynArr tmp=func::Move(*this);
			cap=tmp.cap*2;
			len=size;
			alloc=new typ[cap];
			std::move(tmp.begin(), tmp.end(), alloc);
		}
		else
		{
			DynArr tmp=func::Move(*this);
			cap=len=size;
			alloc=new typ[cap];
			std::move(tmp.begin(), tmp.end(), alloc);
		}
	}
	void increase_size(size_t plus)
	{
		resize(len+plus);
	}
	void decrease_size(size_t minus)
	{
		resize(len-minus);
	}
	void push_back(const typ& value)
	{
		resize(len+1);
		back()=value;
	}
	void push_back(typ&& value)
	{
		resize(len+1);
		back()=func::Move(value);
	}
	void pop_back()
	{
		if(len==0)
			throw std::out_of_range("DynArr is empty!");
		decrease_size(1);
	}
	void erase(size_t index)
	{
		if(index==len-1)
		{
			pop_back();
			return;
		}
		typ last=func::Move(back());
		pop_back();
		for(size_t i=index; i<len-1; ++i)
		{
			alloc[i]=func::Move(alloc[i+1]);
		}
		back()=func::Move(last);
	}
	void reverse()noexcept
	{
		for(size_t i=0; i<(len>>1); ++i)
		{
			Swap(alloc[i],alloc[len-(i+1)]);
		}
		return *this;
	}
	size_t find(const typ& value)const noexcept
	{
		for(size_t i=0; i<len; ++i)
		{
			if(alloc[i]==value)return i;
		}
		return len;
	}
	const DynArr& operator+=(const DynArr& second)noexcept
	{
		resize(len+second.len);
		std::copy(second.begin(), second.end(), alloc+len-second.len);
		return *this;
	}
	DynArr operator+(const DynArr& second)const noexcept
	{
		DynArr result(*this);
		result+=second;
		return result;
	}
	bool operator==(const DynArr& vct)const noexcept
	{
		if(len!=vct.len)
		{
			return false;
		}
		for(size_t i=0; i<len; ++i)
		{
			if(vct[i]!=alloc[i])
			{
				return false;
			}
		}
		return true;
	}
	bool operator!=(const DynArr& vct)const noexcept
	{
		if(len!=vct.len)
		{
			return true;
		}
		for(size_t i=0; i<len; ++i)
		{
			if(vct[i]!=alloc[i])
			{
				return true;
			}
		}
		return false;
	}
	void swap(DynArr& vct)noexcept
	{
		func::Swap(alloc, vct.alloc);
		func::Swap(len,  vct.len);
		func::Swap(cap, vct.cap);
	}
	typ sum()const noexcept
	{
		typ suma=alloc[0];
		for(size_t i=1; i<len; ++i)
		{
			suma+=alloc[i];
		}
		return suma;
	}
	typ avg()const noexcept
	{
		return sum()/len;
	}
	size_t min()const noexcept
	{
		size_t result=0;
		for(size_t i=1; i<len; ++i)
		{
			if(alloc[i]<alloc[result])result=i;
		}
		return result;
	}
	size_t max()const noexcept
	{
		size_t result=0;
		for(size_t i=1; i<len; ++i)
		{
			if(alloc[i]>alloc[result])result=i;
		}
		return result;
	}
};
}