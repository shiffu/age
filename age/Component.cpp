#include "Component.h"

namespace age {
    
    void Component::setGameObject(GameObject* parent) {
        m_parent = parent;
    }
    
}