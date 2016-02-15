#pragma once

#include <string>
#include <vector>

namespace age {

	class ResourceManager
	{
	public:
		bool readFileToBuffer(const std::string& filename, std::vector<unsigned char>& buffer);

	private:
		//TODO: Use new c++11 features to hide those
		ResourceManager();
		~ResourceManager();
	};

}