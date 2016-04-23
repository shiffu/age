#pragma once

#include <vector>
#include <Vertex.h>
#include "Component.h"
#include "IRenderable2D.h"

namespace age {

    class Texture;
    
    class SpriteComponent : public Component, IRenderable2D {
    
    public:
        SpriteComponent(float width, float height);
        ~SpriteComponent();
        
        void setTexture(Texture* texture) { m_texture = texture; }
        
        virtual void render(IRenderer* renderer);
 
        const std::vector<Vertex>& getVertices() const;
        const std::vector<unsigned short>& getIndices() const;
        GLuint getTextureId() const;
        unsigned int getDepth() const;

    private:
        static const unsigned char SPRITE_NB_VERTICES = 4;
        static const unsigned char SPRITE_NB_INDICES = 6;

        float m_width;
        float m_height;
        unsigned int m_depth;
        
        std::vector<Vertex> m_vertices;
        std::vector<Vertex> m_tranformedVertices;
        std::vector<unsigned short> m_indices;
        Texture* m_texture = nullptr;
    };
    
}