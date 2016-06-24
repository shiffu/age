#include "Collider.h"

namespace age {
    
    Collider::Collider(const PhysicsDef& physicsDef, const BoxDef& boxDef, bool isSensor)
        : m_physicsDef(physicsDef), m_boxDef(boxDef), m_isSensor(isSensor) {}
    
    void Collider::addLabel(const std::string& label) {
        m_labels.push_back(label);
    }
    
    std::vector<std::string> Collider::getLabels() const {
        return m_labels;
    }
    
    void Collider::setCollisionAware(bool isCollisionAware) {
        m_isCollisionAware = isCollisionAware;
    }
    
    bool Collider::isCollisionAware() {
        return m_isCollisionAware;
    }

    bool Collider::isTouching(Collider* other) const {
        return m_contacts.find(other) != m_contacts.end();
    }
    
    bool Collider::isTouching(const std::string& otherLabel) const {
        return m_touchingLabels.find(otherLabel) != m_touchingLabels.end();
    }
    
    bool Collider::isTouchingAny(std::vector<const char*> otherLabels) const {
        for (auto otherLabel : otherLabels) {
            if (m_touchingLabels.find(otherLabel) != m_touchingLabels.end())
                return true;
        }
        return false;
    }

    void Collider::beginCollision(Collider* other) {
        m_contacts[other]++;
        for (auto label : other->getLabels()) {
            m_touchingLabels.insert(label);
        }
    }
    
    void Collider::endCollision(Collider* other) {
        auto it = m_contacts.find(other);
        if (it != m_contacts.end()) {
            it->second--;
            if (it->second == 0) {
                m_contacts.erase(it);
                for (auto label : other->getLabels()) {
                    m_touchingLabels.erase(label);
                }
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