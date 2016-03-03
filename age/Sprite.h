#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include "Color.h"
#include "Vertex.h"

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
		void draw();

	private:
		Position2D m_pos;
		float m_width;
		float m_height;
		Color m_color;

		GLuint m_vbo = 0;
        Vertex m_vertexData[6];
	};

}

