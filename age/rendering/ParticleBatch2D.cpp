#include "ParticleBatch2D.h"
#include "IRenderer.h"
#include "Vertex.h"

namespace age {
    
    void defaultUpdateFct(Particle2D& particule, float deltaTime) {
        particule.position += particule.velocity * deltaTime;
    }

    
    ParticleBatch2D::~ParticleBatch2D() {
        delete[] m_particles;
    }
    
    ParticleBatch2D::ParticleBatch2D(int maxParticles, Texture* texture,
                                     float decayRate /* = 0.1f*/,
                                    std::function<void(Particle2D&, float)> updateFct /* = defaultUpdateFct */)
        : m_maxParticules(maxParticles), m_decayRate(decayRate), m_updateFct(updateFct) {
        
        m_texture = texture;
        m_particles = new Particle2D[m_maxParticules];
    }

    void ParticleBatch2D::addParticle(const glm::vec2& pos, float width,
                                        const glm::vec2& velocity, const Color& color) {
        int freeParticuleIdx = findFreeParticuleIdx();
        auto& particle = m_particles[freeParticuleIdx];
        
        particle.life = 1.0f;
        particle.width = width;
        particle.position = pos;
        particle.velocity = velocity;
        particle.color = color;
    }
    
    int ParticleBatch2D::findFreeParticuleIdx() {

        for(int i = m_lastFreeParticuleIdx; i < m_maxParticules; i++) {
            if (m_particles[i].life <= 0.0f) {
                m_lastFreeParticuleIdx = i;
                return m_lastFreeParticuleIdx;
            }
        }
        
        for(int i = 0; i < m_lastFreeParticuleIdx; i++) {
            if (m_particles[i].life <= 0.0f) {
                m_lastFreeParticuleIdx = i;
                return m_lastFreeParticuleIdx;
            }
        }

        return 0;
    }
    
    void ParticleBatch2D::update(float deltaTime) {
        for(int i = 0; i < m_maxParticules; i++) {
            if (m_particles[i].life > 0.0f) {
                m_updateFct(m_particles[i], deltaTime);
                m_particles[i].life -= m_decayRate * deltaTime;
            }
        }
    }
    
    void ParticleBatch2D::draw(IRenderer* renderer) {
        renderer->submit(this);
    }

    // Renderable2D methods
    std::vector<Vertex> ParticleBatch2D::getVertices() const {
        std::vector<Vertex> vertices;
        Vertex v;
        for(int i = 0; i < m_maxParticules; i++) {
            auto& p = m_particles[i];
            if (p.life > 0.0f) {
                float halfWidth = p.width / 2.0f;
                
                v.pos = {p.position.x - halfWidth, p.position.y - halfWidth};
                v.uv = {0, 0};
                v.color = p.color;
                vertices.push_back(v);
                
                v.pos = {p.position.x + halfWidth, p.position.y - halfWidth};
                v.uv = {1, 0};
                v.color = p.color;
                vertices.push_back(v);
                
                v.pos = {p.position.x + halfWidth, p.position.y + halfWidth};
                v.uv = {1, 1};
                v.color = p.color;
                vertices.push_back(v);
                
                v.pos = {p.position.x - halfWidth, p.position.y + halfWidth};
                v.uv = {0, 1};
                v.color = p.color;
                vertices.push_back(v);
            }
        }
        
        return vertices;
    }
    
    std::vector<unsigned short> ParticleBatch2D::getIndices() const {
        std::vector<unsigned short> indices;
        unsigned short offset = 0;
        for(int i = 0; i < m_maxParticules; i++) {
            auto& p = m_particles[i];
            if (p.life > 0.0f) {
                indices.push_back(offset);
                indices.push_back(offset + 1);
                indices.push_back(offset + 2);
                indices.push_back(offset);
                indices.push_back(offset + 2);
                indices.push_back(offset + 3);
                offset += 4;
            }
        }
        
        return indices;
    }
    
    GLenum ParticleBatch2D::getDrawingPrimitive() const {
        return GL_TRIANGLES;
    }

}
