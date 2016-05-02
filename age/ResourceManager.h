#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Texture.h"
#include "TextureAtlas.h"

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
        const std::string getRootPath() const;
        
        void setTextureSubFolder(const std::string& subFolder);
        const std::string getTexturePath(const std::string& filename = "") const;
        
        void setAudioSubFolder(const std::string& subFolder);
        const std::string getAudioPath(const std::string& filename = "") const;
        
		Texture* loadTexture(const std::string& filename);

    protected:
        ResourceManager();
        ~ResourceManager();

	private:
		Texture* fetchTextureFromCache(const std::string& filename);

    private:
        std::string m_rootFolder = "res";
        std::string m_textureSubFolder = "textures";
        std::string m_audioSubFolder = "audio";
        
        std::unordered_map<std::string, Texture*> m_texturesMap;
	};

}