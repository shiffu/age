#pragma once

#include <vector>

#include "Sprite.h"
#include "SpriteBatch.h"

namespace age {
    
    enum class RenderingSortType {
        NONE,
        BACK_TO_FRONT,
        FRONT_TO_BACK,
        TEXTURE
    };
    
    class BatchRenderer2D {
    public:
        BatchRenderer2D();
        ~BatchRenderer2D();
        
        void init();
        void begin(RenderingSortType sortType = RenderingSortType::TEXTURE);
        void end();
        void submit(Sprite* sprite);
        void render();
        
    private:
        RenderingSortType m_renderingSortType = RenderingSortType::NONE;
        std::vector<Sprite*> m_sprites;
        std::vector<SpriteBatch*> m_spriteBatches;
        GLuint m_vbo = 0;
        GLuint m_vao = 0;
        GLuint m_ibo = 0;
    };
    
}