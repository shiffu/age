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

	void Texture::bind(GLenum textureSlot /*= GL_TEXTURE0*/) const {
		glActiveTexture(textureSlot);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	void Texture::unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}