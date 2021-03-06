#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../physics/IRigidBody.h"

namespace age {
    
    class Layer;
    class Component;
    class IRenderer;
    class RigidBodyComponent;
    
    class GameObject {
    public:
        GameObject(Layer* parent = nullptr);
        ~GameObject();
        
        Layer* getLayer() const { return m_parentLayer; }
        
        RigidBodyComponent* createRigidBodyComponent(IRigidBody::Type bodyType, glm::vec2 pos);
        
        void update(unsigned int deltaTime);
        void render(IRenderer* renderer);
        
        void addComponent(Component* component);

        void setPosition(glm::vec2 pos);
        void setPosition(float x, float y);
        const glm::vec2& getPosition() const;

        void setAngle(float angleInRadian);
        float getAngle() const;
        
        void setTransform(glm::mat3 transform);
        glm::mat3& getTransform();

		template<class T>
		T* getComponent() const {
			for (auto comp : m_components) {
				T* result = dynamic_cast<T*>(comp);
				if (result)
					return result;
			}

			return nullptr;
		}
        
        template<class T>
        void deleteComponent() {
            for (int i = 0; i < m_components.size(); i++) {
                T* result = dynamic_cast<T*>(m_components[i]);
                if (result) {
                    std::swap(m_components[i], m_components[m_components.size() - 1]);
                    m_components.pop_back();
                    result = nullptr;
                }
            }
        }
        
    private:
        std::vector<Component*> m_components;
        Layer* m_parentLayer;
		glm::vec2 m_position = glm::vec2();
		float m_angle = 0.0f;
        glm::mat3 m_transform = glm::mat3();
    };
    
}