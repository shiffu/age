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

        GLuint getId() {return m_textureId;}
        
		void bind(GLenum textureSlot = GL_TEXTURE0) const;
		void unbind() const;
        //TODO: Remove this method, used for debugging
        GLuint getId() const { return m_textureId; }

	private:
		GLuint m_textureId;
	};

}