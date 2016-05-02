#include "TextureAtlas.h"
#include "Texture.h"

namespace age {

	TextureAtlas::TextureAtlas(Texture* texture, unsigned short tileWidth, unsigned short tileHeight)
		: m_texture(texture), m_tileWidth(tileWidth), m_tileHeight(tileHeight) {
		
		m_nbCols = texture->m_width / tileWidth;
		m_nbRows = texture->m_height / tileHeight;
	}

	TextureAtlas::~TextureAtlas() {}

	void TextureAtlas::setCurrentFrameIndex(unsigned short index, bool flip) {

		unsigned short tileXIndex = index % m_nbCols;
		unsigned short tileYIndex = index / m_nbCols;

		unsigned short tileWidth = m_tileWidth;
		glm::vec2 blOffset(tileXIndex * m_tileWidth, m_texture->m_height - tileYIndex * m_tileHeight - m_tileHeight);
		
		float x1 = (float)(blOffset.x) / m_texture->m_width;
		float x2 = (float)(blOffset.x + m_tileWidth - 1) / m_texture->m_width;

		if (flip) {
			x1 = (float)(blOffset.x + m_tileWidth - 1) / m_texture->m_width;
			x2 = (float)(blOffset.x) / m_texture->m_width;
		}

		m_texture->setUVs(glm::vec4(x1,
									(float)(blOffset.y) / m_texture->m_height,
									x2,
									(float)(blOffset.y + m_tileHeight - 1) / m_texture->m_height ));
	}
}