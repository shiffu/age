#pragma once

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
		Texture(GLuint textureId);
		~Texture();

		void bind(GLenum textureSlot = GL_TEXTURE0);
		void unbind();

	private:
		GLuint m_textureId;
	};

}