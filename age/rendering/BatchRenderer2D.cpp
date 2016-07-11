#include "BatchRenderer2D.h"

#include <algorithm>
#include <iostream>

#include "Vertex.h"
#include "IRenderable2D.h"

namespace age {
    
    Texture* BatchRenderer2D::m_defaultWhiteTexture = nullptr;
    
    BatchRenderer2D::BatchRenderer2D() {}
    
    BatchRenderer2D::~BatchRenderer2D() {
        if (m_vbo) {
            glDeleteBuffers(1, &m_vbo);
        }
        if (m_ibo) {
            glDeleteBuffers(1, &m_ibo);
        }
        if (m_vao) {
            glDeleteVertexArrays(1, &m_vao);
        }
    }
    
    Texture* BatchRenderer2D::getDefaultWhiteTexture() {
        if (m_defaultWhiteTexture == nullptr) {
            m_defaultWhiteTexture = Texture::createBlankOneByOneTexture();
        }
        
        return m_defaultWhiteTexture;
    }
    
    void BatchRenderer2D::init() {
        
        if (m_vao == 0) {
            glGenVertexArrays(1, &m_vao);
        }
        if (m_vbo == 0) {
            glGenBuffers(1, &m_vbo);
        }
        if (m_ibo == 0) {
            glGenBuffers(1, &m_ibo);
        }
        
        glBindVertexArray(m_vao);
        
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        
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
    }
    
    void BatchRenderer2D::begin(RenderingSortType sortType /* = RenderingSortType::TEXTURE */){
        m_renderingSortType = sortType;
        for (auto renderable : m_renderables) {
            if (renderable->isOwnershipTransfered()) {
                delete renderable;
            }
        }
        for (auto batch : m_spriteBatches) {
            delete batch;
        }
        m_renderables.clear();
        m_spriteBatches.clear();
    }
    
    void BatchRenderer2D::submit(IRenderable2D* renderable) {
        m_renderables.push_back(renderable);
    }
    
    void BatchRenderer2D::end() {
        
        // Sort the IRenderable2Ds
        switch (m_renderingSortType) {
            case RenderingSortType::NONE:
                break;
            case RenderingSortType::TEXTURE:
                std::stable_sort(m_renderables.begin(), m_renderables.end(),
                            [] (IRenderable2D* a, IRenderable2D* b) { return a->getTextureId() < b->getTextureId(); });
                break;
            case RenderingSortType::FRONT_TO_BACK:
                std::stable_sort(m_renderables.begin(), m_renderables.end(),
                            [] (IRenderable2D* a, IRenderable2D* b) { return a->getDepth() < b->getDepth(); });
                break;
            case RenderingSortType::BACK_TO_FRONT:
                std::stable_sort(m_renderables.begin(), m_renderables.end(),
                            [] (IRenderable2D* a, IRenderable2D* b) { return a->getDepth() > b->getDepth(); });
                break;
        }
        
        // Create the SpriteBatches
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        GLuint currentTexId = 0;
        GLuint offset = 0;
        GLuint indiceIdx = 0;
        
        for (auto renderable : m_renderables) {
            auto srcIndices = renderable->getIndices();
            auto nbSrcIndices = srcIndices.size();
            
            GLuint renderableTextureId = renderable->getTextureId();
            if (renderableTextureId == 0) {
                renderableTextureId = getDefaultWhiteTexture()->getId();
            }
            
            if (renderableTextureId != currentTexId) {
                SpriteBatch* sb = new SpriteBatch(static_cast<unsigned int>(nbSrcIndices), indiceIdx, renderableTextureId);
                m_spriteBatches.push_back(sb);
                currentTexId = renderableTextureId;
            }
            else {
                m_spriteBatches.back()->nbIndices += nbSrcIndices;
            }
            
            auto srcVertices = renderable->getVertices();
            vertices.insert(vertices.end(), srcVertices.begin(), srcVertices.end());

            for (auto srcIndice : srcIndices) {
                indices.push_back(offset + srcIndice);
                indiceIdx++;
            }
            offset += srcVertices.size();
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        // Orphan the buffer
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        // Upload vertices
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        // Orphan the buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
        // Upload indices
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
 
    void BatchRenderer2D::render() {
        glBindVertexArray(m_vao);
        for (auto batch : m_spriteBatches) {
            //TODO: Reintroduce Texture Activation and Binding in Texture class
            //SpriteBatch->texture->bind();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, batch->textureId);

            glDrawElements(GL_TRIANGLES, batch->nbIndices, GL_UNSIGNED_INT, (void*)(batch->indicesOffset * sizeof(GLuint)));
            //SpriteBatch->texture->unbind();
            glBindTexture(GL_TEXTURE_2D, 0);

        }
        glBindVertexArray(0);
    }
    
}