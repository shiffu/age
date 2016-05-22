#pragma once

#include "Component.h"
#include "IRigidBody.h"

namespace age {
    
    class RigidBodyComponent : public Component {
    
    public:
        void init(IRigidBody::Type bodyType,
                  glm::vec2 pos, float width, float height);
        
        void setPhysicsParams(float density, float friction, float restitution);
        void update(unsigned int deltaTime);

		IRigidBody* getRigidBody() const;

    private:
        IRigidBody* m_rigidBody = nullptr;
    };
    
}