#pragma once

#include <vector>

#include <Game.h>
#include <Basic2DShader.h>
#include <BatchRenderer2D.h>
#include <Texture.h>
#include <Camera2D.h>
#include <AudioEngine.h>
#include <Layer.h>
#include <Box2DPhysicsEngine.h>
#include <Animator.h>


class MyTestGame : public age::Game {
public:
	MyTestGame();
	~MyTestGame();

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

	age::Animator* m_playerAnimator = nullptr;

    age::Sound* m_sound;
    
    static const unsigned int NB_DYN_SPRITES = 80;
	float m_playerVelocity = 0.0f;
	bool m_playerFlipped = false;
};

