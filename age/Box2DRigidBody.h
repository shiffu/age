#pragma once

#include <map>
#include <vector>
#include "glm/glm.hpp"
#include "IRigidBody.h"
#include "Box2DPhysicsEngine.h"

class b2Body;
class b2World;
class b2Fixture;

namespace age {
    
    class Box2DRigidBody : public IRigidBody {
        
    public:
        Box2DRigidBody(Box2DPhysicsEngine* engine, b2World* world, IRigidBody::Type bodyType, glm::vec2 centerPos);
        ~Box2DRigidBody();
        
        void setFixedRotation(bool fixedRotation) override;
        void addCollider(const char* name, Collider* collider) override;
        const Collider* getCollider(const char* name) const override;

		glm::vec2 getPosition() const override;
		glm::vec2 getVelocity() const override;
		float getAngle() const override;

		void applyForce(const glm::vec2& force) override;
		void applyLinearImpulse(const glm::vec2& force) override;

    private:
		//TODO: Make those transalation (Screen/World) constants configurables.
        constexpr static const float W2P = 40.0f;
        constexpr static const float P2W = 1 / W2P;
        
        // Physics
        float m_density = 0;
        float m_friction = 0;
        float m_restitution = 0;
        b2Body* m_body = nullptr;
        Box2DPhysicsEngine* m_engine;
        std::vector<b2Fixture*> m_fixtures;
        std::map<std::string, Collider*> m_colliders;
    };
    
}