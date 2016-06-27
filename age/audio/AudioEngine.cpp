#include "AudioEngine.h"
#include "../core/Error.h"
#include "../core/ResourceManager.h"

#include <SDL2_mixer/SDL_mixer.h>

namespace age {
    
    AudioEngine::AudioEngine() {
        init();
    }
    
    AudioEngine::~AudioEngine() {
        destroy();
    }
    
    void AudioEngine::init() {
        if (!m_isInitialized) {
            
            // Parameter can be a bitwise combination of:
            // MIX_INIT_FAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
            if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
                fatalError("Mix_Init error: " + std::string(Mix_GetError()));
            }
            
            if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
                fatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
            }
            
            m_isInitialized = true;
        }
    }
    
    void AudioEngine::destroy() {
        if (m_isInitialized) {
            m_isInitialized = false;
            
            for (auto& it : m_soundCache) {
                it.second->destroy();
            }
            
            for (auto& it : m_musicCache) {
                it.second->destroy();
            }
            
            m_soundCache.clear();
            m_musicCache.clear();
            
            Mix_CloseAudio();
            Mix_Quit();
        }
    }
    
    Sound* AudioEngine::loadSound(const std::string& filename) {
        
        Sound* sound = nullptr;
        
        // Try to find the audio in the cache
        const std::string filePath = ResourceManager::instance().getAudioPath(filename);
        auto it = m_soundCache.find(filePath);
        
        if (it == m_soundCache.end()) {
            // Cache miss
            
            sound = new Sound();
            sound->load(filePath);

            m_soundCache[filePath] = sound;
        }
        else {
            sound = it->second;
        }
        
        return sound;
    }
    
    Music* AudioEngine::loadMusic(const std::string& filename) {
        
        Music* music = nullptr;

        // Try to find the audio in the cache
        const std::string filePath = ResourceManager::instance().getAudioPath(filename);
        auto it = m_musicCache.find(filePath);
        
        if (it == m_musicCache.end()) {
            // Cache miss
            music = new Music();
            music->load(filePath);

            m_musicCache[filePath] = music;
        }
        else {
            music = it->second;
        }
        
        return music;
    }
    
}