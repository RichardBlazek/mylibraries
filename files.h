#pragma once

#include <fstream>
#include <vector>
#include "func.h"

namespace file
{
bool UpLine(std::istream& source)
{
	char ch='\0';
	while(ch!='\n')
	{
		source.seekg(source.tellg()-std::streamoff(2), source.beg);
		if(source.tellg()==0)
		{
			return true;
		}
		ch=source.get();
	}
	return false;
}
inline bool Rename(const std::string& oldname, const std::string& newname)
{
	return std::rename(oldname.c_str(), newname.c_str())!=0;
}
inline bool Delete(const std::string& filename)
{
	return std::remove(filename.c_str())!=0;
}
uint64 Size(std::istream& stream)
{
	auto pos=stream.tellg();
	stream.seekg(0, stream.end);
	auto result=stream.tellg();
	stream.seekg(pos, stream.beg);
	return result;
}
uint64 Size(std::ostream& stream)
{
	auto pos=stream.tellp();
	stream.seekp(0, stream.end);
	auto result=stream.tellp();
	stream.seekp(pos, stream.beg);
	return result;
}
std::vector<std::string> GetAllLines(std::istream& in)
{
	std::vector<std::string> result;
	while(in)
	{
		std::string line;
		std::getline(in, line);
		result.push_back(line);
	}
	return func::Move(result);
}
}