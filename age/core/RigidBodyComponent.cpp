#include "RigidBodyComponent.h"

#include "Layer.h"
#include "GameObject.h"
#include "../physics/IPhysicsEngine.h"

namespace age {

    void RigidBodyComponent::init(IRigidBody::Type bodyType, glm::vec2 pos, bool fixedRotation) {
        
        IPhysicsEngine* physicsEngine = m_parent->getLayer()->getPhysicsEngine();
        if (physicsEngine) {
            m_rigidBody = physicsEngine->createRigidBody(bodyType, pos, fixedRotation);
        }
        else {
            //TODO: Log error
        }
    }

    void RigidBodyComponent::update(unsigned int deltaTime) {
        if (m_rigidBody) {
            m_parent->setPosition(m_rigidBody->getPosition());
            m_parent->setAngle(m_rigidBody->getAngle());
        }
    }

	IRigidBody* RigidBodyComponent::getRigidBody() const {
		return m_rigidBody;
	}

}