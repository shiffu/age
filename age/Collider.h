#pragma once

#include <vector>
#include <map>
#include <string>
#include "PhysicsDef.h"
#include "BoxDef.h"

namespace age {
    
    class Collider {
        
    public:
        Collider(const PhysicsDef& physicsDef, const BoxDef& boxDef, bool isSensor=false);
        
        void addLabel(const std::string& label);
        void setCollisionAware(bool isCollisionAware);
        bool isCollisionAware();
        
        bool isTouching(Collider* other);
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
        std::map<Collider*, int> m_contacts;
    };
    
}