#pragma once

#include <vector>

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
	age::ShaderProgram m_basicShaderProgram;
	std::vector<age::Sprite*> m_sprites;
	age::Texture* m_texture = nullptr;
	age::Camera2D m_camera;
};

