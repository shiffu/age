#define GLM_SWIZZLE
#include "SpriteComponent.h"

#include "IRenderer.h"
#include "GameObject.h"
#include "Texture.h"

namespace age {

    SpriteComponent::SpriteComponent(float width, float height) : m_width(width), m_height(height) {
        m_vertices.resize(SPRITE_NB_VERTICES);
        m_tranformedVertices.resize(SPRITE_NB_VERTICES);

        float halfWidth = width / 2.0f;
        float halfHeight = height / 2.0f;
        
        // bottom left
        m_vertices[0].uv.u = 0.0f;
        m_vertices[0].uv.v = 0.0f;
        m_vertices[0].pos = glm::vec2(-halfWidth, -halfHeight);
        m_tranformedVertices[0] = m_vertices[0];
        
        // bottom right
        m_vertices[1].uv.u = 1.0f;
        m_vertices[1].uv.v = 0.0f;
        m_vertices[1].pos = glm::vec2(halfWidth, -halfHeight);
        m_tranformedVertices[1] = m_vertices[1];
        
        // top right
        m_vertices[2].uv.u = 1.0f;
        m_vertices[2].uv.v = 1.0f;
        m_vertices[2].pos = glm::vec2(halfWidth, halfHeight);
        m_tranformedVertices[2] = m_vertices[2];
        
        // top left
        m_vertices[3].uv.u = 0.0f;
        m_vertices[3].uv.v = 1.0f;
        m_vertices[3].pos = glm::vec2(-halfWidth, halfHeight);
        m_tranformedVertices[3] = m_vertices[3];
        
        m_indices.resize(SPRITE_NB_INDICES);
        m_indices[0] = 0;
        m_indices[1] = 1;
        m_indices[2] = 2;
        m_indices[3] = 0;
        m_indices[4] = 2;
        m_indices[5] = 3;
    }
    
    SpriteComponent::~SpriteComponent() {}
    
    void SpriteComponent::render(IRenderer* renderer) {
        glm::mat3 m2wTransform = m_parent->getTransform();
        glm::vec3 tmpPos;
        for (int i = 0; i < m_vertices.size(); i++) {
            tmpPos = m2wTransform * glm::vec3(m_vertices[i].pos, 1.0f);
            m_tranformedVertices[i].pos = tmpPos.xy();
        }
        
        renderer->submit(this);
    }
    
    // IRenderable2D Methodes
    const std::vector<Vertex>& SpriteComponent::getVertices() const {
        return m_tranformedVertices;
    }
    
    const std::vector<unsigned short>& SpriteComponent::getIndices() const {
        return m_indices;
    }
    
    GLuint SpriteComponent::getTextureId() const {
        return m_texture ? m_texture->getId() : 0;
    }
    
    unsigned int SpriteComponent::getDepth() const {
        return m_depth;
    }

}