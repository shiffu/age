#define GLM_SWIZZLE
#include "SpriteComponent.h"

#include "GameObject.h"
#include "../rendering/Sprite.h"

namespace age {

    SpriteComponent::SpriteComponent(Sprite* sprite) {
        m_ownSprite = false;
        m_sprite = sprite;
    }

    SpriteComponent::SpriteComponent(float width, float height,
                                     unsigned short nbXTiles /* = 1*/, unsigned short nbYTiles /* = 1*/) {
        m_ownSprite = true;
        m_sprite = new Sprite(width, height, nbXTiles, nbYTiles);
    }
    
    SpriteComponent::~SpriteComponent() {
        if (m_ownSprite) {
            delete m_sprite;
        }
    }
    
	void SpriteComponent::setTexture(Texture* texture) {
		m_sprite->setTexture(texture);
	}

    void SpriteComponent::update(unsigned int deltaTime) {
        if (m_animator) {
            m_sprite->updateUVFromTexture();
        }
        m_sprite->setTransform(m_parent->getTransform());
    }

    void SpriteComponent::render(IRenderer* renderer) {
        m_sprite->draw(renderer);
    }
}