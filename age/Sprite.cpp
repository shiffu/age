#include "Sprite.h"

#include <cstddef>
#include <iostream>

#include "Vertex.h"

namespace age {

	Sprite::Sprite() {
        m_vertexData.resize(SPRITE_SIZE);

        // bottom left
        m_vertexData[0].uv.u = 0.0f;
        m_vertexData[0].uv.v = 0.0f;
        
        // bottom right
        m_vertexData[1].uv.u = 1.0f;
        m_vertexData[1].uv.v = 0.0f;
        
        // top right
        m_vertexData[2].uv.u = 1.0f;
        m_vertexData[2].uv.v = 1.0f;
        
        // top left
        m_vertexData[3].uv.u = 0.0f;
        m_vertexData[3].uv.v = 1.0f;
    }

	Sprite::~Sprite() {}

	void Sprite::init(float x, float y, float width, float height) {
		m_width = width;
		m_height = height;

        setPosition(x, y);
	}

	void Sprite::setPosition(float x, float y) {
		m_pos.x = x;
		m_pos.y = y;

		// Generate the Quad
        // bottom left
		m_vertexData[0].pos.x = m_pos.x;
		m_vertexData[0].pos.y = m_pos.y;

        // bottom right
		m_vertexData[1].pos.x = m_pos.x + m_width;
		m_vertexData[1].pos.y = m_pos.y;

        // top right
		m_vertexData[2].pos.x = m_pos.x + m_width;
		m_vertexData[2].pos.y = m_pos.y + m_height;

        // top left
		m_vertexData[3].pos.x = m_pos.x;
		m_vertexData[3].pos.y = m_pos.y + m_height;
	}
    
    void Sprite::setAngle(float angle) {
        
        glm::vec2 halfDims(m_width / 2.0f, m_height / 2.0f);
 
        // Get points centered at origin
        glm::vec2 tl(-halfDims.x, halfDims.y);
        glm::vec2 bl(-halfDims.x, -halfDims.y);
        glm::vec2 br(halfDims.x, -halfDims.y);
        glm::vec2 tr(halfDims.x, halfDims.y);

        glm::vec2 blOffset(m_vertexData[0].pos.x, m_vertexData[0].pos.y);
        m_vertexData[0].pos = rotateVertex(bl, angle) + halfDims + blOffset;
        m_vertexData[1].pos = rotateVertex(br, angle) + halfDims + blOffset;
        m_vertexData[2].pos = rotateVertex(tr, angle) + halfDims + blOffset;
        m_vertexData[3].pos = rotateVertex(tl, angle) + halfDims + blOffset;
    }
    
    glm::vec2 Sprite::rotateVertex(const glm::vec2& pos, float angle) {
        glm::vec2 newPos;
        newPos.x = pos.x * cos(angle) - pos.y * sin(angle);
        newPos.y = pos.x * sin(angle) + pos.y * cos(angle);
        
        return newPos;
    }

	void Sprite::setColor(Color color) {
		m_color = color;

		// Set Vertices colors
		for (unsigned int i = 0; i < SPRITE_SIZE; i++) {
			m_vertexData[i].color = m_color;
        }
	}

    void Sprite::setTexture(Texture* texture) {
        m_texture = texture;
    }
    
    void Sprite::setRigidBody(IPhysicsEngine* physicsEngine, IRigidBody::Type bodyType,
                              float density, float friction, float restitution) {
        m_rigidBody = physicsEngine->createRigidBody(bodyType, m_pos, m_width, m_height);
        m_rigidBody->setPhysicsParams(density, friction, restitution);
    }
    
    void Sprite::updateFromPhysics() {
        if (m_rigidBody) {
            glm::vec2 pos = m_rigidBody->getPosition();
            setPosition(pos.x, pos.y);
            float angle = m_rigidBody->getAngle();
            setAngle(angle);
        }
    }
}