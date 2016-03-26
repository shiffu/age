#pragma once

#include <glm/glm.hpp>

class IRigidBody {
public:
    enum class Type {
        STATIC,
        DYNAMIC,
        KINEMATIC
    };
    
    virtual void setPhysicsParams(float density, float friction, float restitution) = 0;
    virtual glm::vec2 getPosition() const = 0;
    virtual float getAngle() const = 0;
};