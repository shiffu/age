#pragma once

namespace age {
    
    class IRenderable2D;
    
    class IRenderer {
        
    public:
        enum class RenderingSortType {
            NONE,
            BACK_TO_FRONT,
            FRONT_TO_BACK,
            TEXTURE
        };
        
        virtual void init() = 0;
        virtual void begin(RenderingSortType sortType = RenderingSortType::TEXTURE) = 0;
        virtual void end() = 0;
        virtual void submit(IRenderable2D* renderable) = 0;
        virtual void render() = 0;
    };
    
}