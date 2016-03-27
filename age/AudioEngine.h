#pragma once

#include <string>
#include <map>

#include "Music.h"
#include "Sound.h"

namespace age {
    
    class AudioEngine {
    public:
        static AudioEngine & instance() {
            static AudioEngine myInstance;
            
            return myInstance;
        }
        
        // delete copy and move constructors and assign operators
        AudioEngine(AudioEngine const&) = delete;             // Copy construct
        AudioEngine(AudioEngine&&) = delete;                  // Move construct
        AudioEngine& operator=(AudioEngine const&) = delete;  // Copy assign
        AudioEngine& operator=(AudioEngine &&) = delete;      // Move assign
        
        void init();
        void destroy();
        
        Sound* loadSound(const std::string& filename);
        Music* loadMusic(const std::string& filename);
        
    private:
        AudioEngine();
        ~AudioEngine();
        
        bool m_isInitialized = false;
        std::map<std::string, Sound*> m_soundCache;
        std::map<std::string, Music*> m_musicCache;
    };
    
}