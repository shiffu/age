#include "RigidBodyComponent.h"

#include "Layer.h"
#include "GameObject.h"
#include "IPhysicsEngine.h"

namespace age {

    void RigidBodyComponent::init(IRigidBody::Type bodyType,
              glm::vec2 pos, float width, float height) {
        
        IPhysicsEngine* physicsEngine = m_parent->getLayer()->getPhysicsEngine();
        if (physicsEngine) {
            m_rigidBody = physicsEngine->createRigidBody(bodyType, pos, width, height);
        }
        else {
            //TODO: Log error
        }
    }

    void RigidBodyComponent::setPhysicsParams(float density, float friction, float restitution) {
        if (m_rigidBody) {
            m_rigidBody->setPhysicsParams(density, friction, restitution);
        }
    }

    void RigidBodyComponent::update(unsigned int deltaTime) {
        if (m_rigidBody) {
            m_parent->setPosition(m_rigidBody->getPosition());
            m_parent->setAngle(m_rigidBody->getAngle());
        }
    }

}