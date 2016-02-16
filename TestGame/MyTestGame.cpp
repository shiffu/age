#include "stdafx.h"
#include "MyTestGame.h"

#include <iostream>
#include <random>

#include <Sprite.h>

MyTestGame::MyTestGame() : age::Game("My First Test Game")
{
}


MyTestGame::~MyTestGame()
{
}

void MyTestGame::onInit() {
	// Init Shader Program
	// TODO: Do not hardcode the path to resources (resourceManager)
	m_basicShaderProgram.compileShaders("../age/shaders/basic");
	m_basicShaderProgram.linkProgram();
	m_basicShaderProgram.bindAttribute("position");
	m_basicShaderProgram.bindAttribute("color");
	m_basicShaderProgram.bindAttribute("uv");

	m_camera.init(1024, 768);

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> posDist(0, 200);
	std::uniform_real_distribution<float> dimDist(100, 450);

	//for (unsigned int i = 0; i < 20; i++) {
	//	age::Sprite* sprite = new age::Sprite();
	//	float x = posDist(mt);
	//	float y = posDist(mt);
	//	float width = dimDist(mt);
	//	float height = dimDist(mt);

	//	sprite->init(x, y, width, height);
	//	m_sprites.push_back(sprite);
	//}

	age::Sprite* sprite = new age::Sprite();
	sprite->init(100.0f, 0.0f, 100.0f, 100.0f);
	m_sprites.push_back(sprite);

	sprite = new age::Sprite();
	sprite->init(300.0f, 0.0f, 100.0f, 100.0f);
	m_sprites.push_back(sprite);

	sprite = new age::Sprite();
	sprite->init(500.0f, 0.0f, 100.0f, 100.0f);
	m_sprites.push_back(sprite);

	sprite = new age::Sprite();
	sprite->init(700.0f, 0.0f, 100.0f, 100.0f);
	m_sprites.push_back(sprite);

	sprite = new age::Sprite();
	sprite->init(400.0f, 100.0f, 100.0f, 100.0f);
	m_sprites.push_back(sprite);

	sprite = new age::Sprite();
	sprite->init(600.0f, 100.0f, 100.0f, 100.0f);
	m_sprites.push_back(sprite);

	//m_texture.load("res/textures/test.png");
	//m_texture.load("res/textures/grass.png");
	m_texture.load("res/textures/mario-brick.png");
}

void MyTestGame::onInput(SDL_Event evt) {
	float speed = 0.015f;

	if (m_inputManager.isKeyPressed(SDLK_a)) {
		Position2D currentPos = m_sprites.back()->getPosition();
		m_sprites.back()->setPosition(currentPos.x - speed, currentPos.y);
	}

	if (m_inputManager.isKeyPressed(SDLK_d)) {
		Position2D currentPos = m_sprites.back()->getPosition();
		m_sprites.back()->setPosition(currentPos.x + speed, currentPos.y);
	}

	if (m_inputManager.isKeyPressed(SDLK_w)) {
		Position2D currentPos = m_sprites.back()->getPosition();
		m_sprites.back()->setPosition(currentPos.x, currentPos.y + speed);
	}

	if (m_inputManager.isKeyPressed(SDLK_s)) {
		Position2D currentPos = m_sprites.back()->getPosition();
		m_sprites.back()->setPosition(currentPos.x, currentPos.y - speed);
	}

}

void MyTestGame::onUpdate() {}

void MyTestGame::onRender() {

	m_camera.update();

	m_basicShaderProgram.bind();
	m_time += 0.03f;

	m_basicShaderProgram.setUniform("time", m_time);
	m_basicShaderProgram.setUniform("projection", m_camera.getProjection());
	
	m_texture.bind();
	m_basicShaderProgram.setUniform("fragTexture", 0);

	for (auto sprite : m_sprites) {
		sprite->draw();
	}

	m_texture.unbind();

	m_basicShaderProgram.unbind();
}

void MyTestGame::onExit() {}
