#pragma once

#include <vector>
#include <functional>

#include <cstdlib>
#include <ctime>

#include <glm/glm.hpp>
#include "Color.h"
#include "IRenderer.h"
#include "Renderable2D.h"

namespace age {
    
    class Particle2D {
    public:
        glm::vec2 position = glm::vec2(0.0f);
        glm::vec2 velocity = glm::vec2(0.0f);
        float life = 0;
        float width;
        Color color;
    };
    
    void defaultUpdateFct(Particle2D& particule, float deltaTime);
    
    class ParticleBatch2D : public Renderable2D {
    public:
        virtual ~ParticleBatch2D();
        ParticleBatch2D(int maxParticles, Texture* texture,
                        float decayRate = 0.1f,
                        std::function<void(Particle2D&, float)> updateFct = defaultUpdateFct);
        
        // Renderable2D pure abstract methods
        std::vector<Vertex> getVertices() const override;
        std::vector<unsigned short> getIndices() const override;
        GLenum getDrawingPrimitive() const;
        
        // Renderable2D abstract methods
        void draw(IRenderer* renderer) override;

        void addParticle(const glm::vec2& pos, float width, const glm::vec2& velocity, const Color& color);
        void update(float deltaTime);
        
    private:
        float m_decayRate;
        Particle2D* m_particles = nullptr;
        int m_maxParticules = 0;
        int m_lastFreeParticuleIdx = 0;
        std::function<void(Particle2D&, float)> m_updateFct;
        
        int findFreeParticuleIdx();
    };
    
}