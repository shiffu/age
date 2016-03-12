#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include <vector>

#include "Color.h"
#include "Vertex.h"
#include "Texture.h"

namespace age {

	class Sprite
	{
        friend class BatchRenderer2D;
        
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height);
		void setPosition(float x, float y);
		Position2D getPosition() const { return m_pos; };
        void setColor(Color color);
        void setTexture(Texture* texture);

	private:
        static const unsigned short SPRITE_SIZE = 6;
		Position2D m_pos;
		float m_width;
		float m_height;
        float m_depth = 0;
		Color m_color;
        Texture* m_texture = nullptr;
        std::vector<Vertex> m_vertexData;
	};

}

