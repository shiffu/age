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
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;

		// Create buffer
		if (m_vbo == 0) {
			glGenBuffers(1, &m_vbo);
		}

		// Generate the Quad
		Vertex vertexData[6];

		// First Triangle
		vertexData[0].pos.x = x;
		vertexData[0].pos.y = y;

		vertexData[1].pos.x = x;
		vertexData[1].pos.y = y + height;

		vertexData[2].pos.x = x + width;
		vertexData[2].pos.y = y;

		// Second Triangle
		vertexData[3].pos.x = x + width;
		vertexData[3].pos.y = y;

		vertexData[4].pos.x = x + width;
		vertexData[4].pos.y = y + height;

		vertexData[5].pos.x = x;
		vertexData[5].pos.y = y + height;

		// Set Vertices colors
		for (unsigned int i = 0; i < 6; i++) {
			vertexData[i].color.value = 0xFFFFFF00;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
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