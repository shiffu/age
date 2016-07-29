#include "TextureAtlas.h"
#include "Texture.h"

namespace age {

    TextureAtlas::TextureAtlas(Texture* texture, unsigned short tileWidth, unsigned short tileHeight)
    : m_tileWidth(tileWidth), m_tileHeight(tileHeight) {
        
        m_textureWidth = texture->getWidth();
        m_textureHeight = texture->getHeight();
        
        m_nbCols = m_textureWidth / tileWidth;
        m_nbRows = m_textureHeight / tileHeight;
    }

	TextureAtlas::~TextureAtlas() {}

    glm::vec4 TextureAtlas::getUV() const {
        return m_uv;
    }

	void TextureAtlas::setCurrentFrameIndex(unsigned short index, bool flip) {

		unsigned short tileXIndex = index % m_nbCols;
		unsigned short tileYIndex = index / m_nbCols;

		glm::vec2 blOffset(tileXIndex * m_tileWidth, m_textureHeight - tileYIndex * m_tileHeight - m_tileHeight);
		
		float x1 = (float)(blOffset.x) / m_textureWidth;
		float x2 = (float)(blOffset.x + m_tileWidth - 1) / m_textureWidth;

		if (flip) {
			x1 = (float)(blOffset.x + m_tileWidth - 1) / m_textureWidth;
			x2 = (float)(blOffset.x) / m_textureWidth;
		}

        m_uv = {x1,
                (float)(blOffset.y) / m_textureHeight,
                x2,
                (float)(blOffset.y + m_tileHeight - 1) / m_textureHeight};
	}
}