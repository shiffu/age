#pragma once

#include <vector>
#include "Vertex.h"
#include "SpriteComponent.h"


namespace age {
    
    class Texture;
    
    class TileComponent : public SpriteComponent {
        
    public:
        TileComponent(float width, float height, unsigned short nbXTiles = 1, unsigned short nbYTiles = 1);
        ~TileComponent();

	protected:
		virtual void updateVerticesUVs();

    private:
        unsigned short m_nbXTiles;
        unsigned short m_nbYTiles;
    };
    
}