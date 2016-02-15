#include "ResourceManager.h"

#include <fstream>

namespace age {

	bool ResourceManager::readFileToBuffer(const std::string& filename, std::vector<unsigned char>& buffer) {

		// Open the file
		std::ifstream file(filename, std::ios::binary);
		if (file.fail()) {
			std::string errMsg = "Fail to load file " + filename;
			perror(errMsg.c_str);
		}

		// Seek to the end
		file.seekg(0, std::ios::end);

		// Get the file size
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		// Read the content
		buffer.resize(fileSize);
		file.read((char*)buffer.data(), fileSize);
		file.close();

		return true;
	}

}
