#pragma once

#include "IRenderable2D.h"

#include <vector>
#include <glm/glm.hpp>

namespace age {
    
    class Texture;
    class IRenderer;
    
    class Sprite : public IRenderable2D {
        
    public:
        
        Sprite(glm::vec2 dims, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);
        Sprite(float width, float height, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);
        virtual ~Sprite();
        
        void setPosition(const glm::vec2& pos);
        void setDims(const glm::vec2& dims);
        void setAngle(float angleInRadian);
        void setTransform(const glm::mat3& m2wTransform);
        
        void setTexture(Texture* texture);
        void setUV(const glm::vec4& uv);
        void updateUVFromTexture();
        const glm::vec4& getUV();
        void setColor(Color color);
        void render(IRenderer* renderer);
        
        // IRenderable2D methodes
        std::vector<Vertex> getVertices() const;
        std::vector<unsigned short> getIndices() const;
        GLuint getTextureId() const;
        unsigned int getDepth() const;
        
    private:
        void updateVerticesUVs();
        void updateVerticesPos();
        void updateModel2WordTransform();
        
    private:
        static const unsigned int NB_VERTICES_PER_TILE = 4;
        static const unsigned int NB_INDICES_PER_TILE = 6;
        
        unsigned short m_nbXTiles;
        unsigned short m_nbYTiles;
        
        float m_width;
        float m_height;
        float m_angle = 0.0f;
        glm::vec2 m_pos {0.0f};
        glm::mat3 m_m2wTransform {1.0f};
        
        unsigned int m_depth = 0;
        
        bool m_uvInitialized = false;
        std::vector<Vertex> m_vertices;
        std::vector<Vertex> m_transformedVertices;
        std::vector<unsigned short> m_indices {0, 1, 2, 0, 2, 3};
        Texture* m_texture = nullptr;
        glm::vec4 m_uv {0.0f, 0.0f, 1.0f, 1.0f};
    };
    
}