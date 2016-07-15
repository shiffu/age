#define GLM_SWIZZLE
#include "Renderable2D.h"

#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include "IRenderer.h"
#include "Texture.h"

namespace age {
    
    void Renderable2D::setPosition(const glm::vec2& pos) {
        m_pos = pos;
        updateModel2WordTransform();
    }
    
    void Renderable2D::setAngle(float angleInRadian) {
        m_angle = angleInRadian;
        updateModel2WordTransform();
    }
    
    void Renderable2D::updateModel2WordTransform() {
        m_m2wTransform = glm::translate(glm::mat3(1.0f), m_pos);
        m_m2wTransform = glm::rotate(m_m2wTransform, m_angle);
    }

    void Renderable2D::setColor(Color color) {
        for (int i = 0; i < m_vertices.size(); i++) {
            m_vertices[i].color = color;
            m_transformedVertices[i].color = color;
        }
    }
    
    void Renderable2D::draw(IRenderer* renderer) {
        glm::vec3 tmpPos;
        for (unsigned int i = 0; i < m_vertices.size(); i++) {
            tmpPos = m_m2wTransform * glm::vec3(m_vertices[i].pos, 1.0f);
            m_transformedVertices[i].pos = tmpPos.xy();
        }
        
        renderer->submit(this);
    }

}