#include "AnimatedSprite.h"

#include "ResourceManager.h"
#include <iostream>

namespace age {
    
    AnimatedSprite::AnimatedSprite(const std::string& spriteSheet, unsigned int nbCols /* = 1*/, unsigned int nbRows /* = 1*/) {
        m_texture = ResourceManager::instance().loadTexture(spriteSheet);
        m_nbCols = nbCols;
        m_nbRows = nbRows;
    }
    
    AnimatedSprite::~AnimatedSprite() {}
    
    void AnimatedSprite::addAnimation(const std::string& name, Animation2D* animation) {
        m_animations[name] = animation;
    }
    
    void AnimatedSprite::playAnimation(const std::string& name, unsigned int deltaTime, bool backward /* = false*/) {
        auto it = m_animations.find(name);
        if (it != m_animations.end()) {
            updateUV(it->second, deltaTime, backward);
        }
    }
    
    void AnimatedSprite::updateUV(Animation2D* animation, unsigned int deltaTime, bool backward) {
        
        if (animation->m_duration == 0) {
            return;
        }
        if (animation->m_playTime > animation->m_duration) {
            animation->m_playTime = 0;
        }
        
        animation->m_playTime += deltaTime;
        unsigned int spriteIdx = animation->m_startIndex
                                    + ((animation->m_playTime % animation->m_duration) / (float)animation->m_duration) * animation->m_nbTiles;
        unsigned int cellXIndex = spriteIdx % m_nbCols;
        unsigned int cellYIndex = spriteIdx / m_nbCols;
        
        float cellWidth = 1.0f / (float)m_nbCols;
        float cellHeight = 1.0f / (float)m_nbRows;
        glm::vec2 blOffset(cellXIndex * cellWidth, cellYIndex * cellHeight);
        
        if (backward) {
            blOffset.x += cellWidth;
            cellWidth *= -1;
        }
        //std::cout << "cellXIndex: " << cellXIndex << ", cellYIndex: " << cellYIndex << "deltaTime: " << deltaTime << std::endl;
        
        // bottom left
        m_vertices[0].uv.u = blOffset.x;
        m_vertices[0].uv.v = blOffset.y;
        
        // bottom right
        m_vertices[1].uv.u = blOffset.x + cellWidth;
        m_vertices[1].uv.v = blOffset.y;
        
        // top right
        m_vertices[2].uv.u = blOffset.x + cellWidth;
        m_vertices[2].uv.v = blOffset.y + cellHeight;
        
        // top left
        m_vertices[3].uv.u = blOffset.x;
        m_vertices[3].uv.v = blOffset.y + cellHeight;
    }

}