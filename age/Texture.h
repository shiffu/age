#pragma once

#include <string>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
#else
    #include <GL/glew.h>
#endif

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