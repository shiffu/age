#pragma once

#include <map>
#include <vector>
#include <string>

namespace age {

	class PropertyFileParser {
	public:
		PropertyFileParser();
		~PropertyFileParser();

		void parse(const std::string& filePath);

		std::string getValue(const std::string& key, std::string defaultValue = "") const;
		std::vector<std::string> getList(const std::string& key) const;

	private:
		std::map<std::string, std::string> m_data = {};
	};

}