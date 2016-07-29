#pragma once

#include <glm/glm.hpp>

namespace age {

	class Texture;

	class TextureAtlas
	{
	public:
		TextureAtlas(Texture* texture, unsigned short tileWidth, unsigned short tileHeight);
		~TextureAtlas();

		void setCurrentFrameIndex(unsigned short index, bool flip);
        glm::vec4 getUV() const;

	private:
        unsigned int m_textureWidth;
        unsigned int m_textureHeight;
		unsigned short m_tileWidth;
		unsigned short m_tileHeight;
		unsigned short m_nbCols;
		unsigned short m_nbRows;
        glm::vec4 m_uv = {};
	};

}