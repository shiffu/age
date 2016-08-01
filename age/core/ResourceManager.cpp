#include "ResourceManager.h"

#include <fstream>
#include <iostream>

#ifndef _WIN32
#include <unistd.h>
#else
#include <direct.h>
#endif

#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "Utils.h"

namespace age {

    ResourceManager::ResourceManager() {}
    
    ResourceManager::~ResourceManager() {
        for(auto& it : m_texturesMap) {
            delete it.second;
        }
    }
    
	bool ResourceManager::readFileToBuffer(const std::string& filename, std::vector<unsigned char>& buffer) const {

		// Open the file
		std::ifstream file(filename, std::ios::binary);
		if (file.fail()) {
			std::string errMsg = "Fail to load file " + filename;
			perror(errMsg.c_str());
		}

		// Seek to the end
		file.seekg(0, std::ios::end);

		// Get the file size
		int fileSize = (int)file.tellg();
		file.seekg(0, std::ios::beg);

		// Read the content
		buffer.resize(fileSize);
		file.read((char*)buffer.data(), fileSize);
		file.close();

		return true;
	}

    void ResourceManager::setRootFolder(const std::string& rootFolder) {
        m_rootFolder = rootFolder;
    }
    
    const std::string ResourceManager::getRootPath() const {
        char buffer[256];
#ifdef _WIN32
        const std::string cwd = std::string(_getcwd(buffer, sizeof(buffer)));
#else
        const std::string cwd = std::string(getcwd(buffer, sizeof(buffer)));
#endif
        std::string filePath = cwd + "/" + m_rootFolder;
        
        return filePath;
    }
    
	Texture* ResourceManager::fetchTextureFromCache(const std::string& filepath) {
		
		Texture* ret = nullptr;

		auto it = m_texturesMap.find(filepath);
		if (it != m_texturesMap.end()) {
			std::cout << "Loading texture " << filepath << std::endl;
			ret = it->second;
		}
		else {
			std::cout << "Loading texture " << filepath << " (cache miss)" << std::endl;
		}

		return ret;
	}

	Texture* ResourceManager::loadTexture(const std::string& filename) {

		const std::string filepath = getTexturePath(filename);
		Texture* texture = fetchTextureFromCache(filepath);
		if (texture)
			return texture;
		
		SDL_Surface *image = IMG_Load(filepath.c_str());
        if(!image) {
            std::cerr << "IMG_Load: " << IMG_GetError() << std::endl;
        }
        else {
            glEnable(GL_BLEND);
            Utils::logGlErrors("glEnable failed");
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            Utils::logGlErrors("glBlendFunc failed");
            
            GLuint textureId;
            glGenTextures(1, &textureId);
            Utils::logGlErrors("glGenTextures failed");
            
            glBindTexture(GL_TEXTURE_2D, textureId);
            Utils::logGlErrors("glBindTexture failed");
            
            int width = image->w;
            int height = image->h;
            int channels = image->format->BytesPerPixel;
            unsigned char* img = (unsigned char*)image->pixels;
            
            // Invert Y
            for(int j = 0; j*2 < height; ++j)
            {
                int index1 = j * width * channels;
                int index2 = (height - 1 - j) * width * channels;
                for(int i = width * channels; i > 0; --i)
                {
                    unsigned char temp = img[index1];
                    img[index1] = img[index2];
                    img[index2] = temp;
                    ++index1;
                    ++index2;
                }
            }
            
            // Select mode thanks to channels
            GLint internalFormat = 0;
            switch(channels) {
                case 1:
                    internalFormat = GL_LUMINANCE;
                    break;
                case 2:
                    internalFormat = GL_LUMINANCE_ALPHA;
                    break;
                case 3:
                    internalFormat = GL_RGB;
                    break;
                case 4:
                    internalFormat = GL_RGBA;
                    break;
            }
            
            GLenum imageFormat = internalFormat;
            if (channels == 4 && image->format->Rmask == 0x00FF0000) {
                imageFormat = GL_BGRA;
            }
            
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
                         image->w, image->h, 0, imageFormat,
                         GL_UNSIGNED_BYTE, image->pixels);
            Utils::logGlErrors("glTexImage2D failed");
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            Utils::logGlErrors("Wrap params failed");
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);
            Utils::logGlErrors("MIN/MAG Filters failed");
            
            glBindTexture(GL_TEXTURE_2D, 0);
            
			// Update the texture dimensions and store it in the cache
			texture = new Texture(textureId);
			texture->m_width = image->w;
			texture->m_height = image->h;
            m_texturesMap[filepath] = texture;
            
            if (image) {
                SDL_FreeSurface(image);
            }
        }

		return texture;
    }

	void ResourceManager::setTextureSubFolder(const std::string& subFolder) {
		m_textureSubFolder = subFolder;
	}

    const std::string ResourceManager::getTexturePath(const std::string& filename /* = ""*/) const {
        return getRootPath() + "/" + m_textureSubFolder + "/" + filename;
    }

	void ResourceManager::setAudioSubFolder(const std::string& subFolder) {
		m_audioSubFolder = subFolder;
	}

	const std::string ResourceManager::getAudioPath(const std::string& filename /* = ""*/) const {
        return getRootPath() + "/" + m_audioSubFolder + "/" + filename;
    }

	void ResourceManager::setFontSubFolder(const std::string& subFolder) {
		m_fontSubFolder = subFolder;
	}

	const std::string ResourceManager::getFontPath(const std::string& filename /* = ""*/) const {
		return getRootPath() + "/" + m_fontSubFolder + "/" + filename;
	}

	void ResourceManager::setThemeSubFolder(const std::string& subFolder) {
		m_themeSubFolder = subFolder;
	}

	const std::string ResourceManager::getThemePath(const std::string& filename /* = ""*/) const {
		return getRootPath() + "/" + m_themeSubFolder + "/" + filename;
	}

}
