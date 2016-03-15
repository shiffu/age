#pragma once

#include <vector>

#include <Game.h>
#include <ShaderProgram.h>
#include <Sprite.h>
#include <BatchRenderer2D.h>
#include <Texture.h>
#include <Camera2D.h>

class b2World;
class b2Body;


class MyTestGame : public age::Game {
public:
	MyTestGame();
	~MyTestGame();

	virtual void onInit();
	virtual void onInput(SDL_Event evt);
	virtual void onUpdate();
	virtual void onRender();
	virtual void onExit();

private:
    constexpr static const float W2P = 30.0f;
    constexpr static const float P2W = 1 / W2P;

	age::ShaderProgram m_basicShaderProgram;
	std::vector<age::Sprite*> m_sprites;
    age::BatchRenderer2D m_batchRenderer;
	age::Camera2D m_camera;
    
    b2World* m_world = nullptr;
    b2Body* m_body = nullptr;
    age::Sprite* m_cubeSprite = nullptr;
};

