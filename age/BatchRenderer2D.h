#pragma once

#include <vector>

#include "SpriteBatch.h"
#include "IRenderer.h"

namespace age {
    
    class BatchRenderer2D : public IRenderer {
    public:
        BatchRenderer2D();
        ~BatchRenderer2D();
        
        void init() override;
        void begin(RenderingSortType sortType = RenderingSortType::TEXTURE) override;
        void end() override;
        void submit(IRenderable2D* renderable) override;
        void render() override;
        
    private:
        RenderingSortType m_renderingSortType = RenderingSortType::NONE;
        std::vector<IRenderable2D*> m_renderables;
        std::vector<SpriteBatch*> m_spriteBatches;
        GLuint m_vbo = 0;
        GLuint m_vao = 0;
        GLuint m_ibo = 0;
    };
    
}