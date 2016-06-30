#define GLM_SWIZZLE
#include "SpriteComponent.h"

#include "../rendering/IRenderer.h"
#include "GameObject.h"
#include "../rendering/Texture.h"

namespace age {

    SpriteComponent::SpriteComponent(float width, float height) : m_width(width), m_height(height) {
        m_vertices.resize(NB_VERTICES);
        m_tranformedVertices.resize(NB_VERTICES);

        float halfWidth = width / 2.0f;
        float halfHeight = height / 2.0f;
        
        // bottom left
        m_vertices[0].pos = glm::vec2(-halfWidth, -halfHeight);
        m_tranformedVertices[0] = m_vertices[0];
        
        // bottom right
        m_vertices[1].pos = glm::vec2(halfWidth, -halfHeight);
        m_tranformedVertices[1] = m_vertices[1];
        
        // top right
        m_vertices[2].pos = glm::vec2(halfWidth, halfHeight);
        m_tranformedVertices[2] = m_vertices[2];
        
        // top left
        m_vertices[3].pos = glm::vec2(-halfWidth, halfHeight);
        m_tranformedVertices[3] = m_vertices[3];
        
        m_indices.resize(NB_INDICES);
        m_indices[0] = 0;
        m_indices[1] = 1;
        m_indices[2] = 2;
        m_indices[3] = 0;
        m_indices[4] = 2;
        m_indices[5] = 3;
    }
    
    SpriteComponent::~SpriteComponent() {}
    
	void SpriteComponent::setTexture(Texture* texture) {
		m_texture = texture;
		m_uvs = m_texture->getUVs();
		updateVerticesUVs();
	}

	void SpriteComponent::updateVerticesUVs() {
		// bottom left
		m_vertices[0].uv = m_uvs.xy();
		m_tranformedVertices[0].uv = m_vertices[0].uv;

		// bottom right
		m_vertices[1].uv = m_uvs.zy();
		m_tranformedVertices[1].uv = m_vertices[1].uv;

		// top right
		m_vertices[2].uv = m_uvs.zw();
		m_tranformedVertices[2].uv = m_vertices[2].uv;

		// top left
		m_vertices[3].uv = m_uvs.xw();
		m_tranformedVertices[3].uv = m_vertices[3].uv;
	}

    void SpriteComponent::render(IRenderer* renderer) {

		// Check for UVs updates (needed in case an animator has been set)
		if (m_animator && m_texture) {
			const glm::vec4& uvs = m_texture->getUVs();
			if (m_uvs != uvs) {
				m_uvs = uvs;
				updateVerticesUVs();
			}
		}

        glm::mat3 m2wTransform = m_parent->getTransform();
        glm::vec3 tmpPos;
        for (unsigned int i = 0; i < m_vertices.size(); i++) {
            tmpPos = m2wTransform * glm::vec3(m_vertices[i].pos, 1.0f);
            m_tranformedVertices[i].pos = tmpPos.xy();
        }
        
        renderer->submit(this);
    }
    
    // IRenderable2D Methodes
    std::vector<Vertex> SpriteComponent::getVertices() const {
        return m_tranformedVertices;
    }
    
    std::vector<unsigned short> SpriteComponent::getIndices() const {
        return m_indices;
    }
    
    GLuint SpriteComponent::getTextureId() const {
        return m_texture ? m_texture->getId() : 0;
    }
    
    unsigned int SpriteComponent::getDepth() const {
        return m_depth;
    }

}