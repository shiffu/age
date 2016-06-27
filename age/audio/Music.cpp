#include "Music.h"
#include "../core/Error.h"

namespace age {
    
    Music::Music() {}
    Music::~Music() {
        destroy();
    }
    
    void Music::destroy() {
        if (m_music != nullptr) {
            Mix_FreeMusic(m_music);
            m_music = nullptr;
        }
    }
    
    void Music::load(const std::string& filePath) {
        
        // If a music already exists, destroy it
        destroy();
        
        m_music = Mix_LoadMUS(filePath.c_str());
        
        // Check for errors
        if (m_music == nullptr) {
            fatalError("Mix_LoadMUS error: " + std::string(Mix_GetError()));
        }
    }

    void Music::play(int loops /* = -1 */) {
        if (m_music != nullptr) {
            Mix_PlayMusic(m_music, loops);
        }
    }
    
    void Music::pause() {
        Mix_PauseMusic();
    }
    
    void Music::stop() {
        Mix_HaltMusic();
    }
    
    void Music::resume() {
        Mix_ResumeMusic();
    }

}
