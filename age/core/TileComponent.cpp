#define GLM_SWIZZLE

#include "TileComponent.h"

#include "../rendering/IRenderer.h"
#include "GameObject.h"
#include "../rendering/Texture.h"

namespace age {
    
    TileComponent::TileComponent(float width, float height, unsigned short nbXTiles, unsigned short nbYTiles)
    : SpriteComponent(width, height), m_nbXTiles(nbXTiles), m_nbYTiles(nbYTiles) {
        
        m_vertices.resize(NB_VERTICES * m_nbXTiles * m_nbYTiles);
        m_tranformedVertices.resize(NB_VERTICES * m_nbXTiles * m_nbYTiles);
        m_indices.resize(NB_INDICES * m_nbXTiles * m_nbYTiles);
        
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
                m_vertices[verticesIndex].uv.u = m_uvs.x;
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

	void TileComponent::updateVerticesUVs() {

		unsigned short verticesIndex = 0;

		for (int j = 0; j < m_nbYTiles; j++) {
			for (int i = 0; i < m_nbXTiles; i++) {
				// bottom left
				m_vertices[verticesIndex].uv.u = m_uvs.x;
				m_vertices[verticesIndex].uv.v = m_uvs.y;
				m_tranformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
				verticesIndex++;

				// bottom right
				m_vertices[verticesIndex].uv.u = m_uvs.z;
				m_vertices[verticesIndex].uv.v = m_uvs.y;
				m_tranformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
				verticesIndex++;

				// top right
				m_vertices[verticesIndex].uv.u = m_uvs.z;
				m_vertices[verticesIndex].uv.v = m_uvs.w;
				m_tranformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
				verticesIndex++;

				// top left
				m_vertices[verticesIndex].uv.u = m_uvs.x;
				m_vertices[verticesIndex].uv.v = m_uvs.w;
				m_tranformedVertices[verticesIndex].uv = m_vertices[verticesIndex].uv;
				verticesIndex++;
			}
		}
	}
}