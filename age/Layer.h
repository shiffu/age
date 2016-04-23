#pragma once

#include <vector>

namespace age {
    
    class GameObject;
    class IRenderer;
    class IPhysicsEngine;
    
    class Layer {
    public:
        Layer();
        virtual ~Layer();
        
        void setPhysicsEngine(IPhysicsEngine* physicsEngine) { m_physicsEngine = physicsEngine; }
        IPhysicsEngine* getPhysicsEngine() const { return m_physicsEngine; }
        GameObject* createGameObject();
        
        virtual void update(unsigned int deltaTime);
        virtual void render(IRenderer* renderer);
        
    private:
        IPhysicsEngine* m_physicsEngine = nullptr;
        std::vector<GameObject*> m_gameObjects;
    };
    
}