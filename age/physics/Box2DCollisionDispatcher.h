#pragma once

#include "ICollisionDispatcher.h"
#include "Collider.h"
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <map>

namespace age {
    
    class Box2DCollisionDispatcher : public ICollisionDispatcher, public b2ContactListener {
    public:
        virtual ~Box2DCollisionDispatcher();
        
        void addCollider(Collider* collider) override;

        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
        
    private:
        std::map<Collider*, Collider*> m_colliders;
    };
}