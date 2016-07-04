#pragma once
#include "Collider.h"

namespace age {
    
    class ICollisionDispatcher {

    public:
        virtual ~ICollisionDispatcher() {};
        
        virtual void addCollider(Collider* collider) = 0;
    };
}