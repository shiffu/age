#include "Texture.h"

#include <iostream>

#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "Utils.h"

namespace age {

    Texture::Texture(GLuint textureId) : m_textureId(textureId){}
	Texture::~Texture() {}

	void Texture::bind(GLenum textureSlot /*= GL_TEXTURE0*/) {
		glActiveTexture(textureSlot);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	void Texture::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}