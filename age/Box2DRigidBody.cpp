#include "Box2DRigidBody.h"

#include <Box2D/Box2D.h>

namespace age {
    
    Box2DRigidBody::Box2DRigidBody(Box2DPhysicsEngine* engine, b2World* world, IRigidBody::Type bodyType,
                                   glm::vec2 centerPos) : m_engine(engine) {

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
        m_body = world->CreateBody(&bodyDef);
    }
 
    Box2DRigidBody::~Box2DRigidBody() {
        for(auto fixture : m_fixtures) {
            m_body->DestroyFixture(fixture);
        }
        m_fixtures.clear();
    }
    
    void Box2DRigidBody::setFixedRotation(bool fixedRotation) {
        m_body->SetFixedRotation(fixedRotation);
    }
    
    void Box2DRigidBody::addCollider(const char* name, Collider* collider) {
        
        b2PolygonShape bodyShape;
        const BoxDef boxDef = collider->getBoxDef();
        const PhysicsDef physicsDef = collider->getPhysicsDef();
        
        float halfWidth = (boxDef.width / 2.0f) * P2W;
        float halfHeight = (boxDef.height / 2.0f) * P2W;
        
        if (boxDef.pos.x == 0.0f && boxDef.pos.y == 0.0f) {
            bodyShape.SetAsBox(halfWidth, halfHeight);
        }
        else {
            const b2Vec2 center(boxDef.pos.x * P2W, boxDef.pos.y * P2W);
            bodyShape.SetAsBox(halfWidth, halfHeight, center, boxDef.angle);
        }
        
        // Fixture holds: user data, density, friction, restitution, isSensor
        // collision filter and shape
        b2FixtureDef fixtureDef;
        fixtureDef.isSensor = collider->isSensor();
        fixtureDef.shape = &bodyShape;
        fixtureDef.density = physicsDef.density;
        fixtureDef.friction = physicsDef.friction;
        fixtureDef.restitution = physicsDef.restitution;
        fixtureDef.userData = static_cast<void*>(collider);
        
        m_fixtures.push_back(m_body->CreateFixture(&fixtureDef));
        
        if (collider->isCollisionAware()) {
            m_engine->getCollisionDispatcher()->addCollider(collider);
        }
        
        m_colliders[name] = collider;
    }
    
    const Collider* Box2DRigidBody::getCollider(const char* name) const {
        auto it = m_colliders.find(name);
        if (it != m_colliders.end())
            return it->second;
        
        return nullptr;
    }
    
    glm::vec2 Box2DRigidBody::getPosition() const {
        b2Vec2 pos = m_body->GetPosition();
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
		m_body->ApplyForce(b2Vec2(force.x, force.y), m_body->GetWorldCenter(), true);
	}

	void Box2DRigidBody::applyLinearImpulse(const glm::vec2& force) {
		m_body->ApplyLinearImpulse(b2Vec2(force.x, force.y), m_body->GetWorldCenter(), true);
	}
}
