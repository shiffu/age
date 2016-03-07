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
#include "Texture.h"

namespace age {

    ResourceManager::ResourceManager() {
        
    }
    
    ResourceManager::~ResourceManager() {
        for(auto& it : m_texturesMap) {
            delete it.second;
        }
    }
    
	bool ResourceManager::readFileToBuffer(const std::string& filename, std::vector<unsigned char>& buffer) {

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
    
    void ResourceManager::setTextureSubFolder(const std::string& subFolder) {
        m_texturesSubFolder = subFolder;
    }
    
    Texture* ResourceManager::loadTexture(const std::string& filename) {

        Texture* tex = nullptr;
        //char *base_path = SDL_GetBasePath();
        char buffer[256];
#ifdef _WIN32
        std::string cwd = std::string(_getcwd(buffer, sizeof(buffer)));
#else
		std::string cwd = std::string(getcwd(buffer, sizeof(buffer)));
#endif

        const std::string filePath = cwd + "/" + m_rootFolder + "/" + m_texturesSubFolder + "/" + filename;
        
        std::cout << "loading texture " << filePath << std::endl;
        
        auto it = m_texturesMap.find(filePath);
        if (it != m_texturesMap.end()) {
            std::cout << "Texture " << filePath << " returned from cache" << std::endl;
            return it->second;
        }
        
        // If not in the cache yet
        SDL_Surface *image = IMG_Load(filePath.c_str());
        
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
            
            GLenum imageFormat = GL_BGRA;
            if (image->format->Rmask == 0xFF) {
                imageFormat = GL_RGBA;
            }
            
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat,
                         image->w, image->h, 0, imageFormat,
                         GL_UNSIGNED_BYTE, image->pixels);
            Utils::logGlErrors("glTexImage2D failed");
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            Utils::logGlErrors("Wrap params failed");
            
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            Utils::logGlErrors("MIN/MAG Filters failed");
            
            if (image) {
                SDL_FreeSurface(image);
            }
            
            tex = new Texture(textureId);
            m_texturesMap[filePath] = tex;
        }
        
        return tex;
    }
}
