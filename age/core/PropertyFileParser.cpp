#include "PropertyFileParser.h"

#include <iostream>
#include <fstream>

#include "StringUtil.h"

namespace age {

	PropertyFileParser::PropertyFileParser()
	{
	}


	PropertyFileParser::~PropertyFileParser()
	{
	}

	void PropertyFileParser::parse(const std::string& filePath) {

		using std::cout;
		using std::endl;
		using std::map;
		using std::string;
		using std::ifstream;

		ifstream ifs(filePath);
		if (ifs.fail()) {
			std::string errMsg = "Fail to load file " + filePath;
			perror(errMsg.c_str());
		}

		if (ifs) {
			string line;
			size_t pos = 0;
			string key;
			string value;

			while (std::getline(ifs, line)) {
				StringUtil::ltrim(line);

				// Check for comments
				if (line[0] == '#') {
					continue;
				}

				// Search for "=" separator (key/value)
				if ((pos = line.find("=")) != string::npos) {
					key = StringUtil::trim(line.substr(0, pos));
					value = StringUtil::trim(line.substr(pos + 1));

					//TODO: Remove this debugging log
					cout << "key:" << key << ", value:" << value << endl;
					m_data[key] = value;
				}
			}

			ifs.close();
		}
		else {
		}
	}

	std::string PropertyFileParser::getValue(const std::string& key, std::string defaultValue /* = "" */) const {
		std::string result = defaultValue;
		auto it = m_data.find(key);
		if (it != m_data.end()) {
			result = it->second;
		}

		return result;
	}

}