#pragma once

#include <string>

#include <GL/glew.h>

namespace age {

	class Texture
	{
	public:
		Texture();
		~Texture();

		void load(const std::string& filename);

		void bind(GLenum textureSlot = GL_TEXTURE0);
		void unbind();

	private:
		GLuint m_texture;
	};

}