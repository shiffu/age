#pragma once

#include <vector>
#include <string>

class StringUtil
{
public:
	static std::string& ltrim(std::string& text);
	static std::string& rtrim(std::string& text);
	static std::string& trim(std::string& text);
	static std::vector<std::string> split(const std::string& str, char delimiter);
};

