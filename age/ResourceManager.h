#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Texture.h"

namespace age {

	class ResourceManager
	{
	public:
        static ResourceManager & instance() {
            static ResourceManager myInstance;
            
            return myInstance;
        }
        
        // delete copy and move constructors and assign operators
        ResourceManager(ResourceManager const&) = delete;             // Copy construct
        ResourceManager(ResourceManager&&) = delete;                  // Move construct
        ResourceManager& operator=(ResourceManager const&) = delete;  // Copy assign
        ResourceManager& operator=(ResourceManager &&) = delete;      // Move assign
        
        bool readFileToBuffer(const std::string& filename, std::vector<unsigned char>& buffer) const;
        void setRootFolder(const std::string& rootFolder);
        void setTextureSubFolder(const std::string& subFolder);
        
        Texture* loadTexture(const std::string& filename);
        
        
    protected:
        ResourceManager();
        ~ResourceManager();
        
    private:
        std::string m_rootFolder = "res";
        std::string m_texturesSubFolder = "textures";
        std::unordered_map<std::string, Texture*> m_texturesMap;
	};

}