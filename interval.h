#pragma once

namespace containers
{
template<typename T>
class Interval
{
private:
	T start, stop, step;
public:
    Interval(T start, T stop, T step):start(start), stop(stop), step(step){}
    class iterator
    {
	private:
		T pos, step, stop;
	public:
		iterator(T pos, T step, T stop):pos(pos), step(step), stop(stop){}
		bool operator==(iterator second)
		{
			return pos==second.pos;
		}
		bool operator!=(iterator second)
		{
			return pos!=second.pos;
		}
		T operator*()const
		{
			return pos;
		}
		void operator++()
		{
			if(step>=0)
			{
				pos=(pos+step>stop)?stop:pos+step;
			}
			else
			{
				pos=(pos+step<stop)?stop:pos+step;
			}
		}
		void operator++(int)
		{
			++(*this);
		}
    };
    iterator begin()
    {
        return iterator(start, step, stop);
    }
    iterator end()
    {
    	return iterator(stop, 0, stop);
    }
    iterator rbegin()
    {
        return iterator(stop+step, -step, start-step);
    }
    iterator rend()
    {
    	return iterator(start-step, 0, start-step);
    }
};
template<typename T>
Interval<T> Range(T count)
{
	return Interval<T>(0, count, 1);
}

template<typename T>
Interval<T> Range(T start, T stop)
{
	return Interval<T>(start, stop, 1);
}

template<typename T>
Interval<T> Range(T start, T stop, T step)
{
	return Interval<T>(start, stop, step);
}
}