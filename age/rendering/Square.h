#pragma once

#include "Renderable2D.h"

#include <vector>
#include <glm/glm.hpp>

namespace age {
    
    class Texture;
    class IRenderer;
    
    class Square : public Renderable2D {
        
    public:
        
        Square(glm::vec2 dims);
        Square(float width, float height);
        virtual ~Square();
        
        void setDims(const glm::vec2& dims);
                
        // Renderable2D methodes
        std::vector<Vertex> getVertices() const override;
        std::vector<unsigned short> getIndices() const override;
        GLenum getDrawingPrimitive() const override;
        
    private:
        void updateVerticesPos();
        
    protected:
        static const unsigned int NB_VERTICES = 4;
        
        float m_width;
        float m_height;
                
        std::vector<unsigned short> m_indices {0, 1, 2, 3, 0};
    };
    
}