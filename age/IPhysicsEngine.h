#pragma once

#include <glm/glm.hpp>
#include "IRigidBody.h"

namespace age {
    
    class IPhysicsEngine {
    public:
        virtual void init(const glm::vec2& gravity) = 0;
        virtual void update() = 0;

        virtual IRigidBody* createRigidBody(IRigidBody::Type bodyType, glm::vec2 pos, float width, float height) = 0;
    };
    
}