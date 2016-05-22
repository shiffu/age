#pragma once

#include "IRigidBody.h"
#include "glm/glm.hpp"

class b2Body;
class b2World;
class b2Fixture;

namespace age {
    
    class Box2DRigidBody : public IRigidBody {
        
    public:
        Box2DRigidBody(b2World* world, IRigidBody::Type bodyType,
                       glm::vec2 centerPos, float halfWidth, float halfHeight);
        
        void setPhysicsParams(float density, float friction, float restitution) override;

		glm::vec2 getPosition() const override;
		glm::vec2 getVelocity() const override;
		float getAngle() const override;

		void applyForce(const glm::vec2& force) override;
		void applyLinearImpulse(const glm::vec2& force) override;

    private:
		//TODO: Make those transalation (Screen/World) constants configurables.
        constexpr static const float W2P = 40.0f;
        constexpr static const float P2W = 1 / W2P;
        
        glm::vec2 m_pos;
		glm::vec2 m_velocity = glm::vec2();
        float m_halfWidth = 0;
        float m_halfHeight = 0;
        
        // Physics
        float m_density = 0;
        float m_friction = 0;
        float m_restitution = 0;
        b2Body* m_body = nullptr;
        b2Fixture* m_fixture = nullptr;
    };
    
}