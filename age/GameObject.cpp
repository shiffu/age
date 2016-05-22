#include "GameObject.h"

#include <iostream>

#include "Layer.h"
#include "Component.h"
#include "RigidBodyComponent.h"

#include <glm/gtx/matrix_transform_2d.hpp>

namespace age {
    
    GameObject::GameObject(Layer* parent) : m_parentLayer(parent) {}
    GameObject::~GameObject() {}

	RigidBodyComponent* GameObject::createRigidBodyComponent(IRigidBody::Type bodyType,
		glm::vec2 pos, float width, float height) {

		RigidBodyComponent* rigidBodyComponent = new RigidBodyComponent;
		addComponent(rigidBodyComponent);

		IPhysicsEngine* physicsEngine = m_parentLayer->getPhysicsEngine();
		if (physicsEngine) {
			rigidBodyComponent->init(bodyType, pos, width, height);
		}
		else {
			//TODO: log Error
			std::cerr << "No Physics Engine binded to parent Layer" << std::endl;
		}

		return rigidBodyComponent;
	}

    void GameObject::update(unsigned int deltaTime) {
        for (Component* comp : m_components) {
            comp->update(deltaTime);
        }
    }
    
    void GameObject::render(IRenderer* renderer) {
        for (Component* comp : m_components) {
            comp->render(renderer);
        }
    }
    
    void GameObject::addComponent(Component* component) {
        component->setGameObject(this);
        m_components.push_back(component);
    }
    
    void GameObject::setPosition(glm::vec2 pos) {
        m_position = pos;
    }
    
    void GameObject::setPosition(float x, float y) {
        m_position = glm::vec2(x, y);
    }
    
    const glm::vec2& GameObject::getPosition() const {
        return m_position;
    }

    void GameObject::setAngle(float angleInRadian) {
        m_angle = angleInRadian;
    }
    
    float GameObject::getAngle() const {
        return m_angle;
    }

    void GameObject::setTransform(glm::mat3 transform) {
        m_transform = transform;
    }
    
    glm::mat3& GameObject::getTransform() {
        m_transform = glm::translate(glm::mat3(), m_position);
        m_transform = glm::rotate(m_transform, m_angle);
        
        return m_transform;
    }

}