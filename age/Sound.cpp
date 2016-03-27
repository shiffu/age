#include "Sound.h"
#include "Error.h"

namespace age {
    
    Sound::Sound() {}
    Sound::~Sound() {
        destroy();
    }

    void Sound::destroy() {
        if (m_chunk != nullptr) {
            Mix_FreeChunk(m_chunk);
        }
    }
    
    void Sound::load(const std::string& filePath) {
        
        // If a chunk already exists, destroy it
        destroy();
        
        m_chunk = Mix_LoadWAV(filePath.c_str());
        
        // Check for errors
        if (m_chunk == nullptr) {
            fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
        }
    }
    
    void Sound::play(int loops /* = 0 */ ) {
        if (m_chunk != nullptr && Mix_PlayChannel(-1, m_chunk, loops) == -1) {
            if (Mix_PlayChannel(0, m_chunk, loops) == -1) {
                fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
            }
        }
    }

}
