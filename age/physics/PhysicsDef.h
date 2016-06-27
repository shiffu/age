#pragma once

namespace age {
    
    struct PhysicsDef {
        float density;
        float friction;
        float restitution;
        
        PhysicsDef() = default;
        
        PhysicsDef(float density, float friction, float restitution) {
            this->density = density;
            this->friction = friction;
            this->restitution = restitution;
        }
    };
    
}