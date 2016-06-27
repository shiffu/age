#pragma once
#include <string>
#include <map>

namespace age {

	class TextureAtlas;
	class Animation2D;

	class Animator
	{
	public:
		Animator(TextureAtlas* textureAtlas);
		~Animator();

		void addAnimation(const std::string& name, Animation2D* animation);
		void playAnimation(const std::string& name, unsigned int deltaTime, bool flip = false);

	private:
		void updateTextureAtlas(Animation2D* animation, unsigned int deltaTime, bool flip);

	private:
		TextureAtlas* m_textureAtlas;
		std::map<std::string, Animation2D*> m_animations;
	};

}
