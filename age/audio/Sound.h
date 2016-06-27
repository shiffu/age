#pragma once

#include <string>

#include <SDL2_mixer/SDL_mixer.h>

namespace age {
    
    class Sound {
    public:
        
        Sound();
        ~Sound();
        
        void load(const std::string& filePath);
        void destroy();

        // Plays the effect file
        // @param loops: If loops == -1, loop forever,
        // otherwise play it loops+1 times
        void play(int loops = 0);
        
    private:
        Mix_Chunk* m_chunk = nullptr;
    };

}