#pragma once

#include <SDL/SDL.h>
#include <Game.h>
#include <ShaderProgram.h>
#include <Sprite.h>
#include <Texture.h>
#include <Camera2D.h>

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
	float m_time = 0;
	age::ShaderProgram m_basicShaderProgram;
	std::vector<age::Sprite*> m_sprites;
	age::Texture m_texture;
	age::Camera2D m_camera;
};

