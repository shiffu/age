#include "Collider.h"
#include <iostream>

namespace age {
    
    Collider::Collider(const PhysicsDef& physicsDef, const BoxDef& boxDef, bool isSensor)
        : m_physicsDef(physicsDef), m_boxDef(boxDef), m_isSensor(isSensor) {}
    
    void Collider::addLabel(const std::string& label) {
        m_labels.push_back(label);
    }
    
    void Collider::setCollisionAware(bool isCollisionAware) {
        m_isCollisionAware = isCollisionAware;
    }
    
    bool Collider::isCollisionAware() {
        return m_isCollisionAware;
    }

    bool Collider::isTouching(Collider* other) {
        return m_contacts.find(other) != m_contacts.end();
    }

    void Collider::beginCollision(Collider* other) {
        m_contacts[other]++;
        //std::cout << "begin collision" << std::endl;
    }
    
    void Collider::endCollision(Collider* other) {
        //std::cout << "end collision" << std::endl;
        auto it = m_contacts.find(other);
        if (it != m_contacts.end()) {
            it->second--;
            if (it->second == 0) {
                m_contacts.erase(it);
            }
        }
    }

    const PhysicsDef& Collider::getPhysicsDef() const {
        return m_physicsDef;
    }
    
    const BoxDef& Collider::getBoxDef() const {
        return m_boxDef;
    }

}