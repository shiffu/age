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
	virtual glm::vec2 getVelocity() const = 0;
	virtual float getAngle() const = 0;

	virtual void applyForce(const glm::vec2& force) = 0;
	virtual void applyLinearImpulse(const glm::vec2& force) = 0;
};