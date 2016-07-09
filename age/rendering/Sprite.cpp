#define GLM_SWIZZLE

#include "Sprite.h"

#include <glm/gtx/matrix_transform_2d.hpp>

#include "Texture.h"
#include "IRenderer.h"

namespace age {
    
    Sprite::Sprite() : Sprite(0.0f, 0.0f) {}
    
    Sprite::Sprite(int width, int height, glm::vec2 pos /* = glm::vec2(0) */)
            : m_width(width), m_height(height), m_pos(pos) {
        
        m_vertices.resize(NB_VERTICES);
        
        updateVerticesPos();
    }
    
    Sprite::~Sprite() {}
    
    void Sprite::setPosition(const glm::vec2& pos) {
        m_pos = pos;
    }
    
    void Sprite::setDims(const glm::vec2& dims) {
        m_width = dims.x;
        m_height = dims.y;
        updateVerticesPos();
    }

    void Sprite::updateVerticesPos() {
        
        float halfWidth = m_width / 2.0f;
        float halfHeight = m_height / 2.0f;
        
        // bottom left
        m_vertices[0].pos = glm::vec2(-halfWidth, -halfHeight);
        
        // bottom right
        m_vertices[1].pos = glm::vec2(halfWidth, -halfHeight);
        
        // top right
        m_vertices[2].pos = glm::vec2(halfWidth, halfHeight);
        
        // top left
        m_vertices[3].pos = glm::vec2(-halfWidth, halfHeight);
        
        /*
        // bottom left
        m_vertices[0].pos = glm::vec2(0, 0);
        
        // bottom right
        m_vertices[1].pos = glm::vec2(m_width, 0);
        
        // top right
        m_vertices[2].pos = glm::vec2(m_width, m_height);
        
        // top left
        m_vertices[3].pos = glm::vec2(0, m_height);
         */
    }
    
    void Sprite::setTexture(Texture* texture) {
        m_texture = texture;
        if (!m_uvInitialized) {
            setUV(m_texture->getUVs());
        }
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
        // bottom left
        m_vertices[0].uv = m_uv.xy();

        // bottom right
        m_vertices[1].uv = m_uv.zy();
        
        // top right
        m_vertices[2].uv = m_uv.zw();
        
        // top left
        m_vertices[3].uv = m_uv.xw();
    }

    void Sprite::setColor(Color color) {
        m_vertices[0].color = color;
        m_vertices[1].color = color;
        m_vertices[2].color = color;
        m_vertices[3].color = color;
    }
    
    void Sprite::render(IRenderer* renderer) {
        glm::mat3 transform = glm::translate(glm::mat3(), m_pos);
        //transform = glm::rotate(transform, m_angle);
        
        glm::vec3 tmpPos;
        for (unsigned int i = 0; i < m_vertices.size(); i++) {
            tmpPos = transform * glm::vec3(m_vertices[i].pos, 1.0f);
            m_vertices[i].pos = tmpPos.xy();
        }

        renderer->submit(this);
    }

    // IRenderable2D Methodes
    std::vector<Vertex> Sprite::getVertices() const {
        return m_vertices;
    }
    
    std::vector<unsigned short> Sprite::getIndices() const {
        return m_indices;
    }
    
    GLuint Sprite::getTextureId() const {
        return m_texture ? m_texture->getId() : 0;
    }
    
    unsigned int Sprite::getDepth() const {
        return m_depth;
    }

}
