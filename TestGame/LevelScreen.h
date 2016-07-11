#pragma once

#include <vector>

#include <core/Game.h>
#include <rendering/Basic2DShader.h>
#include <rendering/BatchRenderer2D.h>
#include <rendering/Texture.h>
#include <rendering/Camera2D.h>
#include <audio/AudioEngine.h>
#include <core/Layer.h>
#include <physics/Box2DPhysicsEngine.h>
#include <rendering/Animator.h>
#include <rendering/ParticleEngine2D.h>
#include <core/Screen.h>
#include <rendering/Sprite.h>


class LevelScreen : public age::Screen {
public:
    LevelScreen(unsigned int level);
    ~LevelScreen();
    
    virtual std::string getNext() const;
    
    virtual void onInit();
    virtual void onExit();
    virtual void onDestroy();
    
    virtual void onEntry();
    virtual void onInput();
    virtual void onUpdate(float deltaTime);
    virtual void onRender();
    
private:
    unsigned int m_level;
    bool m_gameOver = false;
    age::Basic2DShader m_basicShader;
    age::BatchRenderer2D m_batchRenderer;
    age::Camera2D m_camera;
    
    age::Music* m_music = nullptr;
    
    age::Texture* m_brickTexture = nullptr;
    age::Texture* m_metalTexture = nullptr;
    age::Texture* m_particuleTexture = nullptr;
    
    age::Layer* m_sceneLayer = nullptr;
    age::Box2DPhysicsEngine* m_scenePhysicsEngine = nullptr;
    age::GameObject* m_cubeGO = nullptr;
    age::GameObject* m_player = nullptr;
    age::GameObject* m_groundGO = nullptr;
    
    age::ParticleEngine2D* m_particuleEngine = nullptr;
    age::ParticleBatch2D* m_playerParticuleBatch = nullptr;
    
    age::Sprite m_testSprite{50.0f, 50.0f};
    
    age::Animator* m_playerAnimator = nullptr;
    
    age::Sound* m_sound;
    
    static const unsigned int NB_DYN_SPRITES = 80;
    float m_playerVelocity = 0.0f;
    bool m_playerFlipped = false;
    unsigned int m_jumpThreshold = 4;
};