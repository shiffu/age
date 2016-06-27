#pragma once

namespace age {
    
    class GameObject;
    class IRenderer;
    
    class Component {
        
    public:
        Component() {};
        virtual ~Component() {};
        
        void setGameObject(GameObject* parent);
        
        virtual void update(unsigned int deltaTime) {};
        virtual void render(IRenderer* renderer) {};
        
    protected:
        GameObject* m_parent = nullptr;
    };
    
}