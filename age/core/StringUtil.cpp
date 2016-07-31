#include "StringUtil.h"

#include <sstream>
#include <algorithm>

namespace age {

	std::string& StringUtil::ltrim(std::string& text) {
		text.erase(text.begin(), std::find_if(text.begin(), text.end(), [](char& c)->bool { return !isspace(c); }));
		return text;
	}


	std::string& StringUtil::rtrim(std::string& text) {
		text.erase(std::find_if(text.rbegin(), text.rend(), [](char& ch)->bool { return !isspace(ch); }).base(), text.end());
		return text;
	}


	std::string& StringUtil::trim(std::string& text) {
		return ltrim(rtrim(text));
	}

	std::vector<std::string> StringUtil::split(const std::string& str, char delimiter) {
		std::vector<std::string> result;
		std::stringstream ss(str);
		std::string tok;

		while (std::getline(ss, tok, delimiter)) {
			result.push_back(tok);
		}

		return result;
	}

}