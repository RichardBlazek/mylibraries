#pragma once

#include <stdexcept>

template<typename T>
class Optional
{
private:
	T* value=nullptr;
public:
	struct EmptyError: std::logic_error
	{
		using std::logic_error::logic_error;
	};
    constexpr Optional():value(nullptr){}
    Optional(const Optional& opt)
		:value(bool(opt)?new T(*opt.value):nullptr){}
	~Optional()
	{
        delete value;
	}
    Optional& operator=(const Optional& opt)
    {
    	value=bool(opt)?new T(*opt.value):nullptr;
    	return *this;
    }
    Optional(Optional&& opt):value(opt.value)
    {
    	opt.value=nullptr;
    }
    Optional& operator=(Optional&& opt)
    {
    	value=opt.value;
    	opt.value=nullptr;
    	return *this;
    }
    Optional(const T& newvalue)
    {
    	value=new T(newvalue);
    }
    Optional& operator=(const T& newvalue)
    {
    	delete value;
    	value=new T(newvalue);
    	return *this;
    }
    T& Value()const
    {
    	if(!value)throw EmptyError("Optional error");
    	return *value;
    }
    T ValueOr(T a)const
    {
    	return value?*value:a;
    }
    explicit operator bool()const
    {
    	return value;
    }
    void Clear()
    {
    	delete value;
    	value=nullptr;
    }
};