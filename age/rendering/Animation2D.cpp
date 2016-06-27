
#include "Animation2D.h"

namespace age {
    
    Animation2D::Animation2D(unsigned int startIndex, unsigned int nbTiles, unsigned int durationMs) {
        m_startIndex = startIndex;
        m_nbTiles = nbTiles;
        m_duration = durationMs;
    }
    
    Animation2D::~Animation2D() {
    }

}