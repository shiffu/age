#pragma once

#include <vector>
#include "Vertex.h"

namespace age {
    
    class IRenderable2D {
        
    public:
        virtual ~IRenderable2D() {};
        
        virtual std::vector<Vertex> getVertices() const = 0;
        virtual std::vector<unsigned short> getIndices() const = 0;
        virtual GLuint getTextureId() const = 0;
        virtual unsigned int getDepth() const = 0;
        
        void transferOwnership(bool isTransfer) { m_transferOwnership = isTransfer; }
        bool isOwnershipTransfered() { return m_transferOwnership; }
        
    private:
        bool m_transferOwnership = false;
    };
    
}