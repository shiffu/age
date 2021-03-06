#include "Layer.h"

#include "GameObject.h"
#include "../physics/IPhysicsEngine.h"
#include "RigidBodyComponent.h"

namespace age {
    
    Layer::Layer() {}
    
    Layer::~Layer() {
        for(GameObject* go : m_gameObjects) {
            delete go;
        }
        m_gameObjects.clear();
    }
    
    void Layer::destroyPhysicsEngine() {
        for(GameObject* go : m_gameObjects) {
            go->deleteComponent<RigidBodyComponent>();
        }
        delete m_physicsEngine;
        m_physicsEngine = nullptr;
    }

    GameObject* Layer::createGameObject() {
        GameObject* go = new GameObject(this);
        m_gameObjects.push_back(go);
        return go;
    }
    
    void Layer::update(unsigned int deltaTime) {
        if (m_physicsEngine) {
            m_physicsEngine->update();
        }
        for(GameObject* go : m_gameObjects) {
            go->update(deltaTime);
        }
    }
    
    void Layer::render(IRenderer* renderer) {
        for(GameObject* go : m_gameObjects) {
            go->render(renderer);
        }
    }

}