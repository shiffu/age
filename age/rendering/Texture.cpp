#include "Texture.h"

#include <iostream>

#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "../core/Utils.h"

namespace age {

    Texture::Texture(GLuint textureId) : m_textureId(textureId) {}
	Texture::~Texture() {
        if (m_textureId) {
            glDeleteTextures(1, &m_textureId);
            m_textureId = 0;
        }
    }

    Texture* Texture::createBlankOneByOneTexture() {
        GLuint textureID;
        glGenTextures(1, &textureID);
        Texture* texture = new Texture(textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        int pureWhitePixel = 0xFFFFFFFF;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pureWhitePixel);        
        
        // Set some texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);
        
        return texture;
    }

	void Texture::bind(GLenum textureSlot /*= GL_TEXTURE0*/) const {
		glActiveTexture(textureSlot);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	void Texture::unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}