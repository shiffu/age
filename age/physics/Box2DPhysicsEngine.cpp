#include "Box2DPhysicsEngine.h"

#include "Box2DRigidBody.h"
#include <Box2D/Box2D.h>

namespace age {
    
    Box2DPhysicsEngine::Box2DPhysicsEngine() {}
    Box2DPhysicsEngine::~Box2DPhysicsEngine() {}
    
    void Box2DPhysicsEngine::init(const glm::vec2& gravity) {
        if (m_world == nullptr) {
            b2Vec2 b2Gravity(gravity.x, gravity.y);
            m_world = new b2World(b2Gravity);
        }
    }
    
    void Box2DPhysicsEngine::update() {
        if (m_world) {
            m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
        }
    }
    
    ICollisionDispatcher* Box2DPhysicsEngine::getCollisionDispatcher() {
        if (m_collisionDispatcher == nullptr) {
            m_collisionDispatcher = new Box2DCollisionDispatcher();
            m_world->SetContactListener(m_collisionDispatcher);
        }
        
        return m_collisionDispatcher;
    }

    IRigidBody* Box2DPhysicsEngine::createRigidBody(IRigidBody::Type bodyType, glm::vec2 pos, bool fixedRotation) {
        
        Box2DRigidBody* rigidBody = nullptr;
        rigidBody = new Box2DRigidBody(this, m_world, bodyType, pos);
        
        return rigidBody;
    }
    
}
