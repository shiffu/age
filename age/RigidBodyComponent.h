#pragma once

#include "Component.h"
#include "IRigidBody.h"

namespace age {
    
    class RigidBodyComponent : public Component {
    
    public:
        void init(IRigidBody::Type bodyType, glm::vec2 pos, bool fixedRotation=false);
        void update(unsigned int deltaTime);

		IRigidBody* getRigidBody() const;

    private:
        IRigidBody* m_rigidBody = nullptr;
    };
    
}