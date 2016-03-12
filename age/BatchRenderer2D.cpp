#include "BatchRenderer2D.h"

#include <algorithm>

namespace age {
    
    BatchRenderer2D::BatchRenderer2D() {}
    
    BatchRenderer2D::~BatchRenderer2D() {
        if (m_vbo) {
            glDeleteBuffers(1, &m_vbo);
        }
        if (m_vao) {
            glDeleteVertexArrays(1, &m_vao);
        }
    }
    
    void BatchRenderer2D::init() {
        if (m_vao == 0) {
            glGenVertexArrays(1, &m_vao);
        }

        if (m_vbo == 0) {
            glGenBuffers(1, &m_vbo);
        }
        
        glBindVertexArray(m_vao);
        
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        
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
        m_sprites.clear();
        m_spriteBatches.clear();
    }
    
    void BatchRenderer2D::end() {

        // Sort the Sprites
        switch (m_renderingSortType) {
            case RenderingSortType::NONE:
                break;
            case RenderingSortType::BACK_TO_FRONT:
                std::stable_sort(m_sprites.begin(), m_sprites.end(), [] (Sprite* a, Sprite* b) {return a->m_texture < b->m_texture;});
                break;
            case RenderingSortType::FRONT_TO_BACK:
                std::stable_sort(m_sprites.begin(), m_sprites.end(), [] (Sprite* a, Sprite* b) {return a->m_depth < b->m_depth;});
                break;
            case RenderingSortType::TEXTURE:
                std::stable_sort(m_sprites.begin(), m_sprites.end(), [] (Sprite* a, Sprite* b) {return a->m_depth > b->m_depth;});
                break;
        }
        
        // Create the SpriteBatches
        std::vector<Vertex> vertices;
        vertices.reserve(m_sprites.size() * 6);
        GLuint currentTexId = 0;
        GLuint offset = 0;
        for (auto sprite : m_sprites) {
            if (sprite->m_texture->getId() != currentTexId) {
                m_spriteBatches.emplace_back(offset, 6, *(sprite->m_texture));
                currentTexId = sprite->m_texture->getId();
            }
            else {
                m_spriteBatches.back().numVertices += 6;
            }
            
            vertices.insert(vertices.end(), sprite->m_vertexData.begin(), sprite->m_vertexData.end());
            offset += 6;
        }
        
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        // Orphan the buffer
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        // Upload vertices
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0); //TODO: Is this unbind needed?
        glBindVertexArray(0);
    }

    void BatchRenderer2D::submit(Sprite* sprite){
        m_sprites.push_back(sprite);
    }
    
    void BatchRenderer2D::render(){
        glBindVertexArray(m_vao);
        for (auto spriteBatch : m_spriteBatches) {
            spriteBatch.texture.bind();
            glDrawArrays(GL_TRIANGLES, spriteBatch.offset, spriteBatch.numVertices);
            spriteBatch.texture.unbind();
        }
        glBindVertexArray(0);
    }
    
}