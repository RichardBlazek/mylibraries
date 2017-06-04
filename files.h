#pragma once

#include <fstream>
#include "dynarr.h"

namespace file
{
bool UpLine(std::ifstream& source)
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
bool UpLine(std::fstream& source)
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
uint64 Size(std::fstream& file)
{
	uint64 pos=file.tellg();
	file.seekg(0, file.end);
	uint64 result=file.tellg();
	file.seekg(pos, file.beg);
	return result;
}
uint64 Size(std::ifstream& file)
{
	uint64 pos=file.tellg();
	file.seekg(0, file.end);
	uint64 result=file.tellg();
	file.seekg(pos, file.beg);
	return result;
}
uint64 Size(std::ofstream& file)
{
	uint64 pos=file.tellp();
	file.seekp(0, file.end);
	uint64 result=file.tellp();
	file.seekp(pos, file.beg);
	return result;
}
containers::DynArr<std::string> GetAllLines(const std::string& filename)
{
	std::ifstream is(filename);
	containers::DynArr<std::string> result;
	while(!is.eof())
	{
		std::string line;
		std::getline(is, line);
		result.push_back(line);
	}
	return (containers::DynArr<std::string>&&)result;
}
containers::DynArr<std::string> GetAllLines(std::fstream& is)
{
	containers::DynArr<std::string> result;
	while(!is.eof())
	{
		std::string line;
		std::getline(is, line);
		result.push_back(line);
	}
	return (containers::DynArr<std::string>&&)result;
}
containers::DynArr<std::string> GetAllLines(std::ifstream& is)
{
	containers::DynArr<std::string> result;
	while(!is.eof())
	{
		std::string line;
		std::getline(is, line);
		result.push_back(line);
	}
	return (containers::DynArr<std::string>&&)result;
}
}