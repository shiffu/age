#pragma once

#include "IRenderable2D.h"

#include <vector>
#include <glm/glm.hpp>

namespace age {
    
    class Texture;
    class IRenderer;
    
    class Sprite : public IRenderable2D {
        
    public:
        
        Sprite();
        Sprite(int width, int height, glm::vec2 pos = glm::vec2(0));
        virtual ~Sprite();
        
        void setPosition(const glm::vec2& pos);
        void setDims(const glm::vec2& dims);
        void setTexture(Texture* texture);
        void setUV(const glm::vec4& uv);
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

        static const unsigned char NB_VERTICES = 4;
        
        float m_width;
        float m_height;
        glm::vec2 m_pos;
        
        unsigned int m_depth = 0;
        
        bool m_uvInitialized = false;
        glm::vec4 m_uv {0.0f, 0.0f, 1.0f, 1.0f};
        std::vector<Vertex> m_vertices;
        std::vector<unsigned short> m_indices {0, 1, 2, 0, 2, 3};
        Texture* m_texture = nullptr;
    };
    
}