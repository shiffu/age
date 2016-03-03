#include "Texture.h"

#include <iostream>

#include <SOIL/SOIL.h>

namespace age {

	Texture::Texture() {}
	Texture::~Texture() {}

	void Texture::load(const std::string& filename) {
        
        glEnable(GL_TEXTURE_2D);

		// Load an image file directly as a new OpenGL texture
		m_texture = SOIL_load_OGL_texture( filename.c_str(),
											SOIL_LOAD_AUTO,
											SOIL_CREATE_NEW_ID,
											SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_POWER_OF_TWO);

        // Check for an error
		if (m_texture == 0) {
			std::cerr << "Error loading texture " << filename << ": " << SOIL_last_result() << std::endl;
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