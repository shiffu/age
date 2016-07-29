#pragma once

#include "Renderable2D.h"

#include <vector>
#include <glm/glm.hpp>

namespace age {

    class Sprite : public Renderable2D {
        
    public:
        Sprite() {};
        Sprite(glm::vec2 size, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);
        Sprite(float width, float height, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);
        virtual ~Sprite();

        void init(glm::vec2 size, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);
        void init(float width, float height, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);

        void setDims(const glm::vec2& dims);
        
        void setUV(const glm::vec4& uv);
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
        
        unsigned short m_nbXTiles = 1;
        unsigned short m_nbYTiles = 1;
        
        float m_width = 0.0f;
        float m_height = 0.0f;
        
        std::vector<unsigned short> m_indices {0, 1, 2, 0, 2, 3};
        glm::vec4 m_uv {0.0f, 0.0f, 1.0f, 1.0f};
    };
    
}