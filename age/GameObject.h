#pragma once

#include <glm/glm.hpp>

namespace age {
    
    class GameObject {
    public:
        GameObject();
        ~GameObject();
        
    private:
        glm::vec2 m_position;
        float m_angle;
    };
    
}