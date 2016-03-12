#include "Sprite.h"

#include <cstddef>
#include <iostream>

#include "Vertex.h"

namespace age {

	Sprite::Sprite() {
        m_vertexData.resize(SPRITE_SIZE);
    }

	Sprite::~Sprite()
	{
	}

	void Sprite::init(float x, float y, float width, float height) {
		m_width = width;
		m_height = height;

        setPosition(x, y);

		Color defaultColor;
		defaultColor.value = 0xFFFFFFFF;
		setColor(defaultColor);
	}

	void Sprite::setPosition(float x, float y) {
		m_pos.x = x;
		m_pos.y = y;

		// Generate the Quad
		// First Triangle
		m_vertexData[0].pos.x = m_pos.x;
		m_vertexData[0].pos.y = m_pos.y;
		m_vertexData[0].uv.u = 0.0f;
		m_vertexData[0].uv.v = 0.0f;

		m_vertexData[1].pos.x = m_pos.x + m_width;
		m_vertexData[1].pos.y = m_pos.y + m_height;
        m_vertexData[1].uv.u = 1.0f;
		m_vertexData[1].uv.v = 1.0f;

		m_vertexData[2].pos.x = m_pos.x;
		m_vertexData[2].pos.y = m_pos.y + m_height;
		m_vertexData[2].uv.u = 0.0f;
		m_vertexData[2].uv.v = 1.0f;

		// Second Triangle
		m_vertexData[3].pos.x = m_pos.x;
		m_vertexData[3].pos.y = m_pos.y;
		m_vertexData[3].uv.u = 0.0f;
		m_vertexData[3].uv.v = 0.0f;

		m_vertexData[4].pos.x = m_pos.x + m_width;
		m_vertexData[4].pos.y = m_pos.y;
		m_vertexData[4].uv.u = 1.0f;
		m_vertexData[4].uv.v = 0.0f;

		m_vertexData[5].pos.x = m_pos.x + m_width;
		m_vertexData[5].pos.y = m_pos.y + m_height;
		m_vertexData[5].uv.u = 1.0f;
		m_vertexData[5].uv.v = 1.0f;
	}

	void Sprite::setColor(Color color) {
		m_color = color;

		// Set Vertices colors
		for (unsigned int i = 0; i < SPRITE_SIZE; i++) {
			m_vertexData[i].color.value = m_color.value;
        }
	}

    void Sprite::setTexture(Texture* texture) {
        m_texture = texture;
    }
}