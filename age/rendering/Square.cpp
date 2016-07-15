#define GLM_SWIZZLE

#include "IRenderer.h"
#include "Square.h"

#include <glm/gtx/matrix_transform_2d.hpp>


namespace age {
    
    Square::Square(glm::vec2 dims)
        : Square(dims.x, dims.y) {}

    Square::Square(float width, float height) : m_width(width), m_height(height) {
        
        m_vertices.resize(NB_VERTICES);
        m_transformedVertices.resize(NB_VERTICES);
        updateVerticesPos();
    }
    
    Square::~Square() {}
    
    void Square::setDims(const glm::vec2& dims) {
        m_width = dims.x;
        m_height = dims.y;
        updateVerticesPos();
    }
    
    void Square::updateVerticesPos() {
        float halfWidth = m_width / 2.0f;
        float halfHeight = m_height / 2.0f;
        
        // bottom left
        m_vertices[0].pos = glm::vec2(-halfWidth, -halfHeight);
        //m_vertices[0].uv = {0.0f, 0.0f};
        //m_transformedVertices[0].uv = m_vertices[0].uv;
        
        // bottom right
        m_vertices[1].pos = glm::vec2(halfWidth, -halfHeight);
        //m_vertices[1].uv = {1.0f, 0.0f};
        //m_transformedVertices[1].uv = m_vertices[1].uv;
        
        // top right
        m_vertices[2].pos = glm::vec2(halfWidth, halfHeight);
        //m_vertices[2].uv = {1.0f, 1.0f};
        //m_transformedVertices[2].uv = m_vertices[2].uv;
        
        // top left
        m_vertices[3].pos = glm::vec2(-halfWidth, halfHeight);
        //m_vertices[3].uv = {0.0f, 1.0f};
        //m_transformedVertices[3].uv = m_vertices[3].uv;
    }
    
    // Renderable2D Methodes
    std::vector<Vertex> Square::getVertices() const {
        return m_transformedVertices;
    }
    
    std::vector<unsigned short> Square::getIndices() const {
        return m_indices;
    }
    
    GLenum Square::getDrawingPrimitive() const {
        return GL_LINE_STRIP;
    }
}
