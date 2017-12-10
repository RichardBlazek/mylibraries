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
    Optional()=default;
    Optional(const Optional& opt)
		:value(opt.HasValue()?new T(*opt.value):nullptr){}
	~Optional()
	{
        delete value;
	}
    Optional& operator=(const Optional& opt)
    {
    	value=opt.HasValue()?new T(*opt.value):nullptr;
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
    bool HasValue()const
    {
    	return value;
    }
    T& GetValue()const
    {
    	if(!value)throw EmptyError("Optional error");
    	return *value;
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