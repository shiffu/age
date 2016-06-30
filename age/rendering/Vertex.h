#pragma once

#include "Color.h"
#include <glm/glm.hpp>

namespace age {

    struct Vertex {
        glm::vec2 pos;
        Color color;
        glm::vec2 uv;
    };

}