#pragma once

#include "Renderable2D.h"

#include <vector>
#include <glm/glm.hpp>

namespace age {
    
    class Texture;
    class IRenderer;
    
    class Sprite : public Renderable2D {
        
    public:
        
        Sprite(glm::vec2 dims, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);
        Sprite(float width, float height, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);
        virtual ~Sprite();
        
        void setDims(const glm::vec2& dims);
        
        void setTexture(Texture* texture) override;
        void setUV(const glm::vec4& uv);
        void updateUVFromTexture();
        const glm::vec4& getUV();
        
        // Renderable2D methodes
        std::vector<Vertex> getVertices() const override;
        std::vector<unsigned short> getIndices() const override;
        GLenum getDrawingPrimitive() const override;
        
    private:
        void updateVerticesUVs();
        void updateVerticesPos();
        
    private:
        static const unsigned int NB_VERTICES_PER_TILE = 4;
        static const unsigned int NB_INDICES_PER_TILE = 6;
        
        unsigned short m_nbXTiles;
        unsigned short m_nbYTiles;
        
        float m_width;
        float m_height;
        
        bool m_uvInitialized = false;
        std::vector<unsigned short> m_indices {0, 1, 2, 0, 2, 3};
        glm::vec4 m_uv {0.0f, 0.0f, 1.0f, 1.0f};
    };
    
}