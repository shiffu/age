#pragma once
#include "Vertex.h"

namespace age {
    
    class IRenderable2D {
        
    public:
        virtual const std::vector<Vertex>& getVertices() const = 0;
        virtual const std::vector<unsigned short>& getIndices() const = 0;
        virtual GLuint getTextureId() const = 0;
        virtual unsigned int getDepth() const = 0;
    };
    
}