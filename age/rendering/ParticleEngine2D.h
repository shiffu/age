#pragma once

#include "ParticleBatch2D.h"
#include <vector>

namespace age {
    
    class ParticleEngine2D {
    public:
        ParticleEngine2D();
        ~ParticleEngine2D();
        
        // ParticuleEngine2D is responsible of the memory management
        // of the batches
        ParticleBatch2D* createParticuleBatch(int maxParticles, Texture* texture,
                                              float decayRate = 0.1f,
                                              std::function<void(Particle2D&, float)> updateFct = defaultUpdateFct);
        void addParticuleBatch(ParticleBatch2D* batch);
        void update(float deltaTime);
        void render(IRenderer& renderer);
        
    private:
        std::vector<ParticleBatch2D*> m_particuleBatches;
    };
    
}