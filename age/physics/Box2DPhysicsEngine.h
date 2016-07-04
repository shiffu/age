#pragma once

#include "IPhysicsEngine.h"
#include "IRigidBody.h"
#include "Box2DCollisionDispatcher.h"

class b2World;

namespace age {
    
    class Box2DPhysicsEngine : public IPhysicsEngine {
    public:
        Box2DPhysicsEngine();
        virtual ~Box2DPhysicsEngine();
        
        void init(const glm::vec2& gravity) override;
        void update() override;
        ICollisionDispatcher* getCollisionDispatcher() override;
        
        IRigidBody* createRigidBody(IRigidBody::Type bodyType, glm::vec2 pos, bool fixedRotation=false) override;

    private:
        b2World* m_world = nullptr;
        
		//TODO: Make the Step constant configurable
        const float m_timeStep = 1.0f / 60.0f;
        const int m_velocityIterations = 6;
        const int m_positionIterations = 2;
        
        Box2DCollisionDispatcher* m_collisionDispatcher = nullptr;
    };
    
}