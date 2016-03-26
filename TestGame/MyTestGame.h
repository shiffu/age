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
	age::ShaderProgram m_basicShaderProgram;
    age::BatchRenderer2D m_batchRenderer;
	age::Camera2D m_camera;
    
    static const unsigned int NB_DYN_SPRITES = 80;
    std::vector<age::Sprite*> m_containerSprites;
    std::vector<age::Sprite*> m_dynamicSprites;
    std::vector<age::Sprite*> m_backgroundSprites;
};

