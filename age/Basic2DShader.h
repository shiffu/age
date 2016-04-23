#pragma once

#include "ShaderProgram.h"
#include <glm/glm.hpp>

namespace age {
    
    class Basic2DShader : public ShaderProgram {
    public:
        void init();
        void setProjectionMatrix(glm::mat4 projectionMatrix);
    };
    
}