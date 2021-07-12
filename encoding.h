#pragma once

#include <string>
#include <locale>
#include <codecvt>
#include <windows.h>

std::string ConvertDefaultWindowsEncodingToUtf8(std::string src)
{
	int size=MultiByteToWideChar(CP_ACP, 0, src.data(), src.size(), nullptr, 0);
	std::wstring utf16_str(size, 0);
	MultiByteToWideChar(CP_ACP, 0, src.data(), src.size(), &utf16_str[0], size);

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conversion;
	return conversion.to_bytes(utf16_str);
}
std::string ConvertUtf8ToDefaultWindowsEncoding(std::string src)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conversion;
	std::wstring utf16_str=conversion.from_bytes(src);

	int size=WideCharToMultiByte(CP_ACP, 0, utf16_str.data(), utf16_str.size(), 0, 0, 0, 0);
	std::string win_str(size, 0);
	WideCharToMultiByte(CP_ACP, 0, utf16_str.data(), utf16_str.size(), win_str.data(), win_str.size(), 0, 0);
	return win_str;
}