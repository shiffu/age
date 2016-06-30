#pragma once
#include "Vertex.h"

namespace age {
    
    class IRenderable2D {
        
    public:
        virtual std::vector<Vertex> getVertices() const = 0;
        virtual std::vector<unsigned short> getIndices() const = 0;
        virtual GLuint getTextureId() const = 0;
        virtual unsigned int getDepth() const = 0;
    };
    
}