#pragma once

#include <string>
#include <map>

#include "Sprite.h"
#include "Animation2D.h"

namespace age {
    
    class AnimatedSprite : public Sprite {
    public:
        AnimatedSprite(const std::string& spriteSheet, unsigned int nbCols = 1, unsigned int nbRows = 1);
        ~AnimatedSprite();
        
        void addAnimation(const std::string& name, Animation2D* animation);
        void playAnimation(const std::string& name, unsigned int deltaTime, bool backward = false);
        
    private:
        void updateUV(Animation2D* animation, unsigned int deltaTime, bool backward);
        
        unsigned int m_nbCols;
        unsigned int m_nbRows;
        std::map<std::string, Animation2D*> m_animations;
    };
    
}