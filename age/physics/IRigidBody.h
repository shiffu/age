#pragma once

#include <glm/glm.hpp>
#include "PhysicsDef.h"
#include "BoxDef.h"
#include "Collider.h"

namespace age {
    
    class IRigidBody {
    public:
        enum class Type {
            STATIC,
            DYNAMIC,
            KINEMATIC
        };

        IRigidBody() {};
        virtual ~IRigidBody() {};
        
        virtual void setFixedRotation(bool fixedRotation) = 0;
        virtual void addCollider(const char* name, Collider* collider) = 0;
        virtual const Collider* getCollider(const char* name) const = 0;
        
        virtual glm::vec2 getPosition() const = 0;
        virtual glm::vec2 getVelocity() const = 0;
        virtual float getAngle() const = 0;
        
        virtual void applyForce(const glm::vec2& force) = 0;
        virtual void applyLinearImpulse(const glm::vec2& force) = 0;
    };
    
}