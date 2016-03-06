#include "Texture.h"

#include <iostream>

#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "Utils.h"

namespace age {

	Texture::Texture() {}
	Texture::~Texture() {}

	void Texture::load(const std::string& filename) {

        //TODO: Create a resource loader instead of putting the loading logic in the Texture class
        SDL_Surface *image = IMG_Load(filename.c_str());
        
        if(!image) {
            std::cerr << "IMG_Load: " << IMG_GetError() << std::endl;
        }
        else {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glGenTextures(1, &m_texture);
            Utils::logGlErrors("glGenTextures failed");
            
            glBindTexture(GL_TEXTURE_2D, m_texture);
            Utils::logGlErrors("glBindTexture failed");
            
            //TODO: use image->format->BytesPerPixel to select GL_RGBA or GL_RGB
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
        }
	}

	void Texture::bind(GLenum textureSlot /*= GL_TEXTURE0*/) {
		glActiveTexture(textureSlot);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	void Texture::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}