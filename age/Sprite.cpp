#include "Sprite.h"

#include <cstddef>

#include "Vertex.h"

namespace age {

	Sprite::Sprite()
	{
	}


	Sprite::~Sprite()
	{
		if (m_vbo) {
			glDeleteBuffers(1, &m_vbo);
		}
	}

	void Sprite::init(float x, float y, float width, float height) {

		m_width = width;
		m_height = height;
		setPosition(x, y);

		Color defaultColor;
		defaultColor.value = 0xFFFFFF00;
		setColor(defaultColor);
	}

	void Sprite::setPosition(float x, float y) {
		m_pos.x = x;
		m_pos.y = y;

		// Create buffer if needed
		if (m_vbo == 0) {
			glGenBuffers(1, &m_vbo);
		}

		// Generate the Quad
		// First Triangle
		m_vertexData[0].pos.x = m_pos.x;
		m_vertexData[0].pos.y = m_pos.y;

		m_vertexData[1].pos.x = m_pos.x;
		m_vertexData[1].pos.y = m_pos.y + m_height;

		m_vertexData[2].pos.x = m_pos.x + m_width;
		m_vertexData[2].pos.y = m_pos.y;

		// Second Triangle
		m_vertexData[3].pos.x = m_pos.x + m_width;
		m_vertexData[3].pos.y = m_pos.y;

		m_vertexData[4].pos.x = m_pos.x + m_width;
		m_vertexData[4].pos.y = m_pos.y + m_height;

		m_vertexData[5].pos.x = m_pos.x;
		m_vertexData[5].pos.y = m_pos.y + m_height;

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexData), m_vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::setColor(Color color) {
		m_color = color;

		// Create buffer if needed
		if (m_vbo == 0) {
			glGenBuffers(1, &m_vbo);
		}

		// Set Vertices colors
		for (unsigned int i = 0; i < 6; i++) {
			m_vertexData[i].color.value = m_color.value;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexData), m_vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw() {
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		// Vertex position pointer
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		
		// Vertex color pointer
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}