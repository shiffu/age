#pragma once

#include <vector>
#include <unordered_set>
#include <map>
#include <string>
#include "PhysicsDef.h"
#include "BoxDef.h"

namespace age {
    
    class Collider {
        
    public:
        Collider(const PhysicsDef& physicsDef, const BoxDef& boxDef, bool isSensor=false);
        ~Collider() {};
        
        void addLabel(const std::string& label);
        std::vector<std::string> getLabels() const;
        
        void setCollisionAware(bool isCollisionAware);
        bool isCollisionAware();
        
        bool isTouching(Collider* other) const;
        bool isTouching(const std::string& otherLabel) const;
        bool isTouchingAny(std::vector<const char*> otherLabels) const;
        
        void beginCollision(Collider* other);
        void endCollision(Collider* other);
        
        const PhysicsDef& getPhysicsDef() const;
        const BoxDef& getBoxDef() const;
        bool isSensor() const { return m_isSensor; }
        
    private:
        PhysicsDef m_physicsDef;
        BoxDef m_boxDef;
        bool m_isSensor;
        bool m_isCollisionAware = false;
        std::vector<std::string> m_labels;
        std::unordered_set<std::string> m_touchingLabels;
        std::map<Collider*, int> m_contacts;
    };
    
}