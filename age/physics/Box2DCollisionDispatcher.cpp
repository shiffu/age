#include "Box2DCollisionDispatcher.h"

#include <Box2D/Dynamics/Contacts/b2Contact.h>

namespace age {
    
    void Box2DCollisionDispatcher::addCollider(Collider* collider) {
        m_colliders[collider] = collider;
    }
    
    void Box2DCollisionDispatcher::BeginContact(b2Contact* contact) {
        Collider* colliderA = static_cast<Collider*>(contact->GetFixtureA()->GetUserData());
        Collider* colliderB = static_cast<Collider*>(contact->GetFixtureB()->GetUserData());

        auto it = m_colliders.find(colliderA);
        if (it != m_colliders.end()) {
            it->second->beginCollision(colliderB);
        }
        
        it = m_colliders.find(colliderB);
        if (it != m_colliders.end()) {
            it->second->beginCollision(colliderA);
        }
    }
    
    void Box2DCollisionDispatcher::EndContact(b2Contact* contact) {
        Collider* colliderA = static_cast<Collider*>(contact->GetFixtureA()->GetUserData());
        Collider* colliderB = static_cast<Collider*>(contact->GetFixtureB()->GetUserData());
        
        auto it = m_colliders.find(colliderA);
        if (it != m_colliders.end()) {
            it->second->endCollision(colliderB);
        }
        
        it = m_colliders.find(colliderB);
        if (it != m_colliders.end()) {
            it->second->endCollision(colliderA);
        }
    }

}