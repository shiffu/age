#pragma once

#include "Component.h"
#include "../physics/IRigidBody.h"

namespace age {
    
    class RigidBodyComponent : public Component {
    
    public:
        virtual ~RigidBodyComponent() { delete m_rigidBody; };

        void init(IRigidBody::Type bodyType, glm::vec2 pos, bool fixedRotation=false);
        void update(unsigned int deltaTime);

		IRigidBody* getRigidBody() const;

    private:
        IRigidBody* m_rigidBody = nullptr;
    };
    
}