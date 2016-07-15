#pragma once

#include <vector>
#include "Vertex.h"
#include "Texture.h"

namespace age {
    
    enum class DrawingPrimitive {
        TRIANGLES,
        TRIANGLES_STRIP,
        LINES,
        LINES_STRIP
    };
    

    class IRenderer;
    
    class Renderable2D {
        
    public:
        virtual ~Renderable2D() {};
        
        // Pure Abstract methodes to be defined in the children classes
        virtual std::vector<Vertex> getVertices() const = 0;
        virtual std::vector<unsigned short> getIndices() const = 0;
        virtual GLenum getDrawingPrimitive() const = 0;
        
        // Abstract methodes (could be overriden by children classes)
        virtual void setTexture(Texture* texture) { m_texture = texture; }
        virtual void draw(IRenderer* renderer);

        void setDepth(unsigned int depth) { m_depth = depth; }
        unsigned int getDepth() const { return m_depth; }
        void setPosition(const glm::vec2& pos);
        void setAngle(float angleInRadian);
        void setTransform(const glm::mat3& m2wTransform) { m_m2wTransform = m2wTransform; }
        
        Texture* getTexture() const { return m_texture; }
        GLuint getTextureId() const { return m_texture ? m_texture->getId() : 0; }

        void setColor(Color color);
        
        void transferOwnership(bool isTransfer) { m_transferOwnership = isTransfer; }
        bool isOwnershipTransfered() { return m_transferOwnership; }
        
    private:
        void updateModel2WordTransform();

    private:
        bool m_transferOwnership = false;

        unsigned int m_depth = 0;
        float m_angle = 0.0f;
        glm::vec2 m_pos {0.0f};
        glm::mat3 m_m2wTransform {1.0f};
        
    protected:
        Texture* m_texture = nullptr;
        std::vector<Vertex> m_vertices;
        std::vector<Vertex> m_transformedVertices;
    };
    
}