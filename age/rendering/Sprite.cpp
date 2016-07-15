#define GLM_SWIZZLE

#include "Sprite.h"

#include <glm/gtx/matrix_transform_2d.hpp>

#include "Texture.h"
#include "IRenderer.h"

namespace age {
    
    Sprite::Sprite(glm::vec2 dims, unsigned short nbXTiles /* = 1*/, unsigned short nbYTiles /* = 1*/)
        : Sprite(dims.x, dims.y, nbXTiles, nbYTiles) {}

    Sprite::Sprite(float width, float height, unsigned short nbXTiles, unsigned short nbYTiles)
        : m_width(width), m_height(height), m_nbXTiles(nbXTiles), m_nbYTiles(nbYTiles) {
        
        m_vertices.resize(NB_VERTICES_PER_TILE * m_nbXTiles * m_nbYTiles);
        m_transformedVertices.resize(NB_VERTICES_PER_TILE * m_nbXTiles * m_nbYTiles);
        m_indices.resize(NB_INDICES_PER_TILE * m_nbXTiles * m_nbYTiles);
        
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
                m_vertices[verticesIndex].uv = m_uv.xy();
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(0.0f, 0.0f);
                m_transformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
                verticesIndex++;
                
                // bottom right
                m_vertices[verticesIndex].uv = m_uv.zy();
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(spriteWidth, 0.0f);
                m_transformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
                verticesIndex++;
                
                // top right
                m_vertices[verticesIndex].uv = m_uv.zw();
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(spriteWidth, spriteHeight);
                m_transformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
                verticesIndex++;
                
                // top left
                m_vertices[verticesIndex].uv = m_uv.xw();
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(0.0f, spriteHeight);
                m_transformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
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
    
    Sprite::~Sprite() {}
    
    void Sprite::setDims(const glm::vec2& dims) {
        m_width = dims.x;
        m_height = dims.y;
        updateVerticesPos();
    }
    
    void Sprite::updateVerticesPos() {
        float halfWidth = m_width / 2.0f;
        float halfHeight = m_height / 2.0f;
        float spriteWidth = m_width / m_nbXTiles;
        float spriteHeight = m_height / m_nbYTiles;
        unsigned short verticesIndex = 0;
        glm::vec2 blSpriteOffset;
        
        for (int j = 0; j < m_nbYTiles; j++) {
            for (int i = 0; i < m_nbXTiles; i++) {
                
                blSpriteOffset = glm::vec2(-halfWidth + spriteWidth * i, -halfHeight + spriteHeight * j);
                
                // bottom left
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(0.0f, 0.0f);
                verticesIndex++;
                
                // bottom right
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(spriteWidth, 0.0f);
                verticesIndex++;
                
                // top right
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(spriteWidth, spriteHeight);
                verticesIndex++;
                
                // top left
                m_vertices[verticesIndex].pos = blSpriteOffset + glm::vec2(0.0f, spriteHeight);
                verticesIndex++;
            }
        }
    }
    
    void Sprite::setTexture(Texture* texture) {
        m_texture = texture;
        if (!m_uvInitialized) {
            setUV(m_texture->getUVs());
        }
    }

    void Sprite::updateUVFromTexture() {
        setUV(m_texture->getUVs());
    }
    
    void Sprite::setUV(const glm::vec4& uv) {
        m_uvInitialized = true;
        m_uv = uv;
        updateVerticesUVs();
    }

    const glm::vec4& Sprite::getUV() {
        return  m_uv;
    }
    
    void Sprite::updateVerticesUVs() {
        unsigned short verticesIndex = 0;
        
        for (int j = 0; j < m_nbYTiles; j++) {
            for (int i = 0; i < m_nbXTiles; i++) {
                
                // bottom left
                m_vertices[verticesIndex].uv = m_uv.xy();
                m_transformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
                verticesIndex++;
                
                // bottom right
                m_vertices[verticesIndex].uv = m_uv.zy();
                m_transformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
                verticesIndex++;
                
                // top right
                m_vertices[verticesIndex].uv = m_uv.zw();
                m_transformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
                verticesIndex++;
                
                // top left
                m_vertices[verticesIndex].uv = m_uv.xw();
                m_transformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
                verticesIndex++;
            }
        }
    }

    // Renderable2D Methodes
    std::vector<Vertex> Sprite::getVertices() const {
        return m_transformedVertices;
    }
    
    std::vector<unsigned short> Sprite::getIndices() const {
        return m_indices;
    }
        
    GLenum Sprite::getDrawingPrimitive() const {
        return GL_TRIANGLES;
    }

}
