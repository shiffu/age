#pragma once

#include "Color.h"
#include <glm/glm.hpp>

namespace age {

    struct UV {
        float u;
        float v;
    };
    
    struct Vertex {
        glm::vec2 pos;
        Color color;
        UV uv;
    };

}