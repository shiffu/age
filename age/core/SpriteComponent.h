#pragma once

#include <vector>
#include "../rendering/Vertex.h"
#include "Component.h"
#include "../rendering/Renderable2D.h"

namespace age {

    class Texture;
	class Animator;
    class Sprite;

    class SpriteComponent : public Component {
    
    public:
        SpriteComponent(Sprite* sprite);
        SpriteComponent(float width, float height, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);
        virtual ~SpriteComponent();
        
		void setTexture(Texture* texture);
		void setAnimator(Animator* animator) { m_animator = animator;  }

        virtual void update(unsigned int deltaTime);
        virtual void render(IRenderer* renderer);
 
	private:
		Animator* m_animator = nullptr;        
        bool m_ownSprite = true;
        Sprite* m_sprite = nullptr;
    };
    
}