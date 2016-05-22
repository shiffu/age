#include "Box2DRigidBody.h"

#include <Box2D/Box2D.h>

namespace age {
    
    Box2DRigidBody::Box2DRigidBody(b2World* world, IRigidBody::Type bodyType,
                                   glm::vec2 centerPos, float halfWidth, float halfHeight) {

        m_halfWidth = halfWidth * P2W;
        m_halfHeight = halfHeight * P2W;

        b2BodyDef bodyDef;
        switch (bodyType) {
            case IRigidBody::Type::DYNAMIC:
                bodyDef.type = b2_dynamicBody;
                break;
            case IRigidBody::Type::KINEMATIC:
                bodyDef.type = b2_kinematicBody;
                break;
            case IRigidBody::Type::STATIC:
                bodyDef.type = b2_staticBody;
                break;
                
            default:
                break;
        }
        
        bodyDef.position.Set(centerPos.x * P2W, centerPos.y * P2W);
		//TODO: Remove this hardcoded fixedRotation = true
		bodyDef.fixedRotation = true;
        m_body = world->CreateBody(&bodyDef);
    }
 
    void Box2DRigidBody::setPhysicsParams(float density, float friction, float restitution) {
        m_density = density;
        m_friction = friction;
        m_restitution = restitution;

        if (m_fixture) {
            m_body->DestroyFixture(m_fixture);
            m_fixture = nullptr;
        }
        
        b2PolygonShape bodyShape;
        bodyShape.SetAsBox(m_halfWidth, m_halfHeight);
        
		// Fixture hold: user data, density, friction, restitution, isSensor
		// collision filter and shape
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &bodyShape;
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        fixtureDef.restitution = restitution;
        
        m_fixture = m_body->CreateFixture(&fixtureDef);
    }
    
    glm::vec2 Box2DRigidBody::getPosition() const {
        b2Vec2 pos = m_body->GetPosition();
		//glm::vec2 returnedPosition = glm::vec2((pos.x - m_halfWidth) * W2P, (pos.y - m_halfHeight) * W2P);
		glm::vec2 returnedPosition = glm::vec2(pos.x * W2P, pos.y * W2P);

		return returnedPosition;
    }

	glm::vec2 Box2DRigidBody::getVelocity() const {
		b2Vec2 v = m_body->GetLinearVelocity();
		return glm::vec2(v.x, v.y);
	}
    
    float Box2DRigidBody::getAngle() const {
        return m_body->GetAngle();
    }

	void Box2DRigidBody::applyForce(const glm::vec2& force) {
		/*
		force = mass * acceleration OR force = mass * (dv/dt)
		
		dv = newVelocity - previousVelocity;
			=> newVelocity = previousVelocity + dv
		AND
		dv/dt = force / mass
			=> dv = (force / mass) * dt
		*/
		//TODO: Remove this hardcoded 1/60 time and make it configurable
		glm::vec2 deltaVelocity = force / m_body->GetMass() * (1 / 60.0f);
		b2Vec2 v = m_body->GetLinearVelocity();
		glm::vec2 newVelocity =  glm::vec2(v.x, v.y) + deltaVelocity;

		m_body->ApplyForce(b2Vec2(force.x, force.y), m_body->GetWorldCenter(), true);
	}

	void Box2DRigidBody::applyLinearImpulse(const glm::vec2& force) {
		m_body->ApplyLinearImpulse(b2Vec2(force.x, force.y), m_body->GetWorldCenter(), true);
	}
}
