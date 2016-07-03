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


class MyTestGame : public age::Game {
public:
	MyTestGame();
	~MyTestGame();

    // Game virtual methods
	virtual void onInit();
	virtual void onInput(SDL_Event evt);
	virtual void onUpdate(unsigned int deltaTime);
	virtual void onRender();
	virtual void onExit();

private:
	age::Basic2DShader m_basicShader;
    age::BatchRenderer2D m_batchRenderer;
	age::Camera2D m_camera;

	age::Layer* m_sceneLayer = nullptr;
    age::Box2DPhysicsEngine* m_scenePhysicsEngine = nullptr;
    age::GameObject* m_cubeGO = nullptr;
	age::GameObject* m_player = nullptr;
    
    age::ParticleEngine2D* m_particuleEngine = nullptr;
    age::ParticleBatch2D* m_playerParticuleBatch = nullptr;
    
	age::Animator* m_playerAnimator = nullptr;

    age::Sound* m_sound;
    
    static const unsigned int NB_DYN_SPRITES = 80;
	float m_playerVelocity = 0.0f;
	bool m_playerFlipped = false;
    unsigned int m_jumpThreshold = 4;
};

