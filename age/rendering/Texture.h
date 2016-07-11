#pragma once

#include <glm/glm.hpp>

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
		friend class TextureAtlas;

		Texture(GLuint textureId);
		~Texture();

        static Texture* createBlankOneByOneTexture();
        
        GLuint getId() const { return m_textureId; }
        unsigned int getWidth() const { return m_width; }
        unsigned int getHeight() const { return m_height; }
		
		// bottom left: {x, y}, top right: {z, w}
		void setUVs(glm::vec4 uvs) { m_uvs = uvs; }
		const glm::vec4& getUVs() const { return m_uvs; }
        
		void bind(GLenum textureSlot = GL_TEXTURE0) const;
		void unbind() const;

	private:
		GLuint m_textureId;
		glm::vec4 m_uvs{0.0f, 0.0f, 1.0f, 1.0f};
        unsigned int m_width = 0;
        unsigned int m_height = 0;
	};

}