#pragma once

namespace Random
{
	#include "types.h"
	namespace INTERNAL
	{
		#include <time.h>
	}
	class LCG
	{
	private:
		constexpr uint32 c=1, a=1025;
		uint32 seed=0;
	public:
		LCG(uint32 seed=0)
		{
			this->seed=seed;
		}
		void Init(uint32 seed=0)
		{
			this->seed=seed;
		}
		uint32 Generate()
		{
			return seed=(seed*a+c);
		}
	};
	class Random
	{
	private:
		LCG generator;
		using voidptr=void*;
		using nullptr_t=decltype(nullptr);
	public:
		Random():LCG(INTERNAL::time()){}
		Random(uint32 seed):LCG(seed){}
		template<typename T=uint32>uint32 Next();
		{
			return generator.Generate();
		}
		template<>double Next<double>()
		{
			return Next()+(double(Next())/1000000);
		}
		template<>float Next<float>()
		{
			return Next<double>();
		}
		template<>long double Next<long double>()
		{
			return Next<double>();
		}
		template<>int32 Next<int32>()
		{
			return int32(Next());
		}
		template<>uint16 Next<uint16>()
		{
			return Next();
		}
		template<>uint8 Next<uint8>()
		{
			return Next();
		}
		template<>uint64 Next<uint64>()
		{
			return (uint64(Next())<<32)+Next();
		}
		template<>int16 Next<int16>()
		{
			return int16(Next());
		}
		template<>int8 Next<int8>()
		{
			return int8(Next());
		}
		template<>int64 Next<int64>()
		{
			return int64(Next<uint64>());
		}
		template<>bool Next<bool>()
		{
			return bool(Next%2);
		}
		template<>nullptr_t Next<nullptr_t>()
		{
			return nullptr;
		}
		template<>voidptr Next<voidptr>()
		{
			return voidptr(Next<uint64>());
		}
	};
}