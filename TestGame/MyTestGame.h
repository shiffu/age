#pragma once

#include <vector>

#include <Game.h>
#include <Basic2DShader.h>
#include <Sprite.h>
#include <BatchRenderer2D.h>
#include <Texture.h>
#include <Camera2D.h>
#include <AudioEngine.h>
#include <AnimatedSprite.h>
#include <Layer.h>
#include <Box2DPhysicsEngine.h>

class b2World;
class b2Body;


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
    
    age::Sound* m_sound;
    
    static const unsigned int NB_DYN_SPRITES = 80;
    age::AnimatedSprite* m_player = nullptr;
    float m_playerVelocity = 0.0f;
    
    std::vector<age::Sprite*> m_containerSprites;
    std::vector<age::Sprite*> m_dynamicSprites;
    std::vector<age::Sprite*> m_backgroundSprites;
};

