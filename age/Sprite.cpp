#include "Sprite.h"

#include <cstddef>
#include <iostream>

#include "Vertex.h"

namespace age {

	Sprite::Sprite() {}

	Sprite::~Sprite()
	{
        if (m_vbo) {
            glDeleteBuffers(1, &m_vbo);
        }
        if (m_vao) {
            glDeleteVertexArrays(1, &m_vao);
        }
	}

	void Sprite::init(float x, float y, float width, float height) {
		m_width = width;
		m_height = height;
        
        // Create buffers if needed
        if (m_vbo == 0) {
            glGenBuffers(1, &m_vbo);
        }
        if (m_vao == 0) {
            glGenVertexArrays(1, &m_vao);
        }

        setPosition(x, y);

		Color defaultColor;
		defaultColor.value = 0xFFFFFFFF;
        /*
        defaultColor.rgba.r = 255;
        defaultColor.rgba.g = 255;
        defaultColor.rgba.b = 255;
        defaultColor.rgba.a = 255;
         */
        
		setColor(defaultColor);
	}

	void Sprite::setPosition(float x, float y) {
        m_isUpdateVaoNeeded = true;
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
        m_isUpdateVaoNeeded = true;
		m_color = color;

		// Set Vertices colors
		for (unsigned int i = 0; i < SPRITE_SIZE; i++) {
			m_vertexData[i].color.value = m_color.value;
        }
	}

    void Sprite::setTexture(Texture* texture) {
        m_texture = texture;
    }
    
    void Sprite::updateVao() {
        if (m_isUpdateVaoNeeded) {
            
            glBindVertexArray(m_vao);
            
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexData), m_vertexData, GL_STATIC_DRAW);
                
                // Vertex position pointer
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
                glEnableVertexAttribArray(0);
                
                // Vertex color pointer
                glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
                glEnableVertexAttribArray(1);
                
                // Vertex uv pointer
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
                glEnableVertexAttribArray(2);

            glBindVertexArray(0);
            m_isUpdateVaoNeeded = false;
        }
    }
    
	void Sprite::draw() {
        updateVao();
        if (m_texture) {
            m_texture->bind();
        }
        
        glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        
        if (m_texture) {
            m_texture->unbind();
        }
	}
}