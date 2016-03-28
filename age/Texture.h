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
        friend class ResourceManager;
        
		Texture(GLuint textureId);
		~Texture();

        GLuint getId() const { return m_textureId; }
        unsigned int getWidth() const { return m_width; }
        unsigned int getHeight() const { return m_height; }
        
		void bind(GLenum textureSlot = GL_TEXTURE0) const;
		void unbind() const;

	private:
		GLuint m_textureId;
        unsigned int m_width = 0;
        unsigned int m_height = 0;
	};

}