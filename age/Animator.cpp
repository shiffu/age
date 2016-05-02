#include "Animator.h"
#include "Animation2D.h"
#include "TextureAtlas.h"

namespace age {

	Animator::Animator(TextureAtlas* textureAtlas) : m_textureAtlas(textureAtlas) {}
	Animator::~Animator() {}

	void Animator::addAnimation(const std::string& name, Animation2D* animation) {
		m_animations[name] = animation;
	}

	void Animator::playAnimation(const std::string& name, unsigned int deltaTime, bool flip /* = false*/) {
		auto it = m_animations.find(name);
		if (it != m_animations.end()) {
			updateTextureAtlas(it->second, deltaTime, flip);
		}
	}

	void Animator::updateTextureAtlas(Animation2D* animation, unsigned int deltaTime, bool flip) {

		if (animation->m_duration == 0) {
			return;
		}

		if (animation->m_playTime > animation->m_duration) {
			animation->m_playTime = 0;
		}

		animation->m_playTime += deltaTime;
		unsigned int frameIdx = animation->m_startIndex
			+ ((animation->m_playTime % animation->m_duration) / (float)animation->m_duration) * animation->m_nbTiles;

		m_textureAtlas->setCurrentFrameIndex(frameIdx, flip);
	}

}