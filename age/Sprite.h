#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include "Color.h"
#include "Vertex.h"
#include "Texture.h"

namespace age {

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height);
		void setPosition(float x, float y);
		Position2D getPosition() const { return m_pos; };
        void setColor(Color color);
        void setTexture(Texture* texture);
		void draw();

	private:
        void updateVao();
        
        static const unsigned short SPRITE_SIZE = 6;
		Position2D m_pos;
		float m_width;
		float m_height;
		Color m_color;
        Texture* m_texture = nullptr;

        bool m_isUpdateVaoNeeded = true;
        GLuint m_vbo = 0;
        GLuint m_vao = 0;
        Vertex m_vertexData[SPRITE_SIZE];
	};

}

