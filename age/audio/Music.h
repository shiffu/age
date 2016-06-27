#pragma once

#include <string>

#include <SDL2_mixer/SDL_mixer.h>

namespace age {
    
    class Music {
    public:
        
        Music();
        ~Music();
        
        void destroy();
        
        void load(const std::string& filePath);
        
        // Plays the music file
        // @param loops: If loops == -1, loop forever,
        // otherwise play it loops times
        void play(int loops = 1);
        
        // Pauses whatever song is currently playing
        void pause();
        
        // Stops whatever song is currently playing
        void stop();
        
        // Resumes whatever song is currently playing
        void resume();
        
    private:
        Mix_Music* m_music = nullptr;
    };

}