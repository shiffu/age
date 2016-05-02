#pragma once

namespace age {

    class Animation2D {
    public:
        friend class Animator;
        
        Animation2D(unsigned int startIndex, unsigned int nbTiles, unsigned int durationMs);
        ~Animation2D();
        
    private:
        unsigned int m_startIndex;
        unsigned int m_nbTiles;
        unsigned int m_duration;
		unsigned int m_currentIndex = 0;
		unsigned int m_playTime = 0;
	};

}