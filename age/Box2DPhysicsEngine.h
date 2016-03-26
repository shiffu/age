#pragma once

#include "IPhysicsEngine.h"
#include "IRigidBody.h"

class b2World;

namespace age {
    
    class Box2DPhysicsEngine : public IPhysicsEngine {
    public:
        Box2DPhysicsEngine();
        ~Box2DPhysicsEngine();
        
        void init(const glm::vec2& gravity) override;
        void update() override;
        
        IRigidBody* createRigidBody(IRigidBody::Type bodyType, glm::vec2 pos, float width, float height) override;

        // TODO: Remove this method which exposes the implementation
        b2World* getB2World() const {return m_world;}
        
    private:
        b2World* m_world = nullptr;
        
        const float m_timeStep = 1.0f / 60.0f;
        const int m_velocityIterations = 6;
        const int m_positionIterations = 2;
    };
    
}