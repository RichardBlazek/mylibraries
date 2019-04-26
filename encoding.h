#pragma once

#include <string>
#include <locale>
#include <codecvt>
#include <windows.h>

std::string ConvertDefaultWindowsEncodingToUtf8(std::string src)
{
	int size=MultiByteToWideChar(CP_ACP, 0, src.c_str(), src.size(), nullptr, 0);
	std::wstring utf16_str(size, '\0');
	MultiByteToWideChar(CP_ACP, 0, src.c_str(), src.size(), &utf16_str[0], size);

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conversion;
	return conversion.to_bytes(utf16_str);
}