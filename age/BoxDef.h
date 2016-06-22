#pragma once

#include <glm/glm.hpp>

namespace age {
    
    struct BoxDef {
        glm::vec2 pos{0.0f};
        float width;
        float height;
        float angle;
        
        BoxDef() = default;
        
        BoxDef(float width, float height) {
            this->width = width;
            this->height = height;
        }
        
        BoxDef(const glm::vec2& pos, float width, float height, float angle=0.0f) {
            this->pos = pos;
            this->width = width;
            this->height = height;
            this->angle = angle;
        }
    };
    
}