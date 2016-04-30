#pragma once

#include <vector>
#include "Vertex.h"
#include "Component.h"
#include "IRenderable2D.h"

namespace age {
    
    class Texture;
    
    class TileComponent : public Component, IRenderable2D {
        
    public:
        TileComponent(float width, float height, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);
        ~TileComponent();
        
        void setTexture(Texture* texture) { m_texture = texture; }
        
        virtual void render(IRenderer* renderer);
        
        const std::vector<Vertex>& getVertices() const;
        const std::vector<unsigned short>& getIndices() const;
        GLuint getTextureId() const;
        unsigned int getDepth() const;
        
    private:
        static const unsigned char NB_VERTICES_PER_SPRITE = 4;
        static const unsigned char NB_INDICES_PER_SPRITE = 6;
        
        float m_width;
        float m_height;
        unsigned short m_nbXTiles;
        unsigned short m_nbYTiles;
        unsigned int m_depth;
        
        std::vector<Vertex> m_vertices;
        std::vector<Vertex> m_tranformedVertices;
        std::vector<unsigned short> m_indices;
        Texture* m_texture = nullptr;
    };
    
}