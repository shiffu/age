#pragma once

namespace age {

	class Texture;

	class TextureAtlas
	{
	public:
		TextureAtlas(Texture* texture, unsigned short tileWidth, unsigned short tileHeight);
		~TextureAtlas();

		void setCurrentFrameIndex(unsigned short index, bool flip);

	private:
		Texture* m_texture;
		unsigned short m_tileWidth;
		unsigned short m_tileHeight;
		unsigned short m_nbCols;
		unsigned short m_nbRows;
	};

}