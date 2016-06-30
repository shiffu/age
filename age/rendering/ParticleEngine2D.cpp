#include "ParticleEngine2D.h"

namespace age {
 
    ParticleEngine2D::ParticleEngine2D() {}
    
    ParticleEngine2D::~ParticleEngine2D() {
        for(ParticleBatch2D* batch : m_particuleBatches) {
            delete batch;
        }
    }
    
    ParticleBatch2D* ParticleEngine2D::createParticuleBatch(int maxParticles, GLuint textureId,
                                                            float decayRate /* = 0.1f */,
                                                            std::function<void(Particle2D&, float)> updateFct /* = defaultUpdateFct */) {
        
        ParticleBatch2D* batch = new ParticleBatch2D(maxParticles, textureId, decayRate, updateFct);
        m_particuleBatches.push_back(batch);
        return batch;
    }

    void ParticleEngine2D::addParticuleBatch(ParticleBatch2D* batch) {
        m_particuleBatches.push_back(batch);
    }
    
    void ParticleEngine2D::update(float deltaTime) {
        for(ParticleBatch2D* batch : m_particuleBatches) {
            batch->update(deltaTime);
        }
    }

    void ParticleEngine2D::render(IRenderer& renderer) {
        for(ParticleBatch2D* batch : m_particuleBatches) {
            batch->render(renderer);
        }
    }

}
