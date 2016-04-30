#define GLM_SWIZZLE

#include "TileComponent.h"

#include "IRenderer.h"
#include "GameObject.h"
#include "Texture.h"

namespace age {
    
    TileComponent::TileComponent(float width, float height, unsigned short nbXTiles, unsigned short nbYTiles)
    : m_width(width), m_height(height), m_nbXTiles(nbXTiles), m_nbYTiles(nbYTiles) {
        
        m_vertices.resize(NB_VERTICES_PER_SPRITE * m_nbXTiles * m_nbYTiles);
        m_tranformedVertices.resize(NB_VERTICES_PER_SPRITE * m_nbXTiles * m_nbYTiles);
        m_indices.resize(NB_INDICES_PER_SPRITE * m_nbXTiles * m_nbYTiles);
        
        float halfWidth = width / 2.0f;
        float halfHeight = height / 2.0f;
        float spriteWidth = width / nbXTiles;
        float spriteHeight = height / nbYTiles;
        unsigned short indiceOffset = 0;
        unsigned short verticesIndex = 0;
        unsigned short indicesIndex = 0;
        glm::vec2 blSpriteOffset;
        
        
        for (int j = 0; j < m_nbYTiles; j++) {
            for (int i = 0; i < m_nbXTiles; i++) {
                
                blSpriteOffset = glm::vec2(-halfWidth + spriteWidth * i, -halfHeight + spriteHeight * j);
                
                // bottom left
                m_vertices[verticesIndex].uv.u = 0.0f;
                m_vertices[verticesIndex].uv.v = 0.0f;
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(0.0f, 0.0f);
                m_tranformedVertices[verticesIndex] = m_vertices[verticesIndex];
                verticesIndex++;
                
                // bottom right
                m_vertices[verticesIndex].uv.u = 1.0f;
                m_vertices[verticesIndex].uv.v = 0.0f;
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(spriteWidth, 0.0f);
                m_tranformedVertices[verticesIndex] = m_vertices[verticesIndex];
                verticesIndex++;
                
                // top right
                m_vertices[verticesIndex].uv.u = 1.0f;
                m_vertices[verticesIndex].uv.v = 1.0f;
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(spriteWidth, spriteHeight);
                m_tranformedVertices[verticesIndex] = m_vertices[verticesIndex];
                verticesIndex++;
                
                // top left
                m_vertices[verticesIndex].uv.u = 0.0f;
                m_vertices[verticesIndex].uv.v = 1.0f;
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(0.0f, spriteHeight);
                m_tranformedVertices[verticesIndex] = m_vertices[verticesIndex];
                verticesIndex++;
                
                m_indices[indicesIndex++] = indiceOffset;
                m_indices[indicesIndex++] = indiceOffset + 1;
                m_indices[indicesIndex++] = indiceOffset + 2;
                m_indices[indicesIndex++] = indiceOffset;
                m_indices[indicesIndex++] = indiceOffset + 2;
                m_indices[indicesIndex++] = indiceOffset + 3;
                indiceOffset += 4;
            }
        }
    }
    
    TileComponent::~TileComponent() {}
    
    void TileComponent::render(IRenderer* renderer) {
        glm::mat3 m2wTransform = m_parent->getTransform();
        glm::vec3 tmpPos;
        for (int i = 0; i < m_vertices.size(); i++) {
            tmpPos = m2wTransform * glm::vec3(m_vertices[i].pos, 1.0f);
            m_tranformedVertices[i].pos = tmpPos.xy();
        }
        
        renderer->submit(this);
    }
    
    // IRenderable2D Methodes
    const std::vector<Vertex>& TileComponent::getVertices() const {
        return m_tranformedVertices;
    }
    
    const std::vector<unsigned short>& TileComponent::getIndices() const {
        return m_indices;
    }
    
    GLuint TileComponent::getTextureId() const {
        return m_texture ? m_texture->getId() : 0;
    }
    
    unsigned int TileComponent::getDepth() const {
        return m_depth;
    }
    
}