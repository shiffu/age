#include "PropertyFileParser.h"

#include <iostream>
#include <fstream>

#include "StringUtil.h"

namespace age {

	using namespace std;

	PropertyFileParser::PropertyFileParser()
	{
	}


	PropertyFileParser::~PropertyFileParser()
	{
	}

	void PropertyFileParser::parse(const std::string& filePath) {

		ifstream ifs(filePath);
		if (ifs.fail()) {
			string errMsg = "Fail to load file " + filePath;
			perror(errMsg.c_str());
		}

		if (ifs) {
			string line;
			size_t pos = 0;
			string key;
			string value;

			while (getline(ifs, line)) {
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

	string PropertyFileParser::getValue(const string& key, string defaultValue /* = "" */) const {
		string result = defaultValue;
		auto it = m_data.find(key);
		if (it != m_data.end()) {
			result = it->second;
		}

		return result;
	}

	vector<string> PropertyFileParser::getList(const string& key) const {
		vector<string> result{};
		auto it = m_data.find(key);
		if (it != m_data.end()) {
			result = StringUtil::split(it->second, ',');
		}

		return result;
	}
}