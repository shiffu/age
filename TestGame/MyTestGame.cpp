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

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> posDist(-0.8, 0.8);
	std::uniform_real_distribution<float> dimDist(0.1, 0.4);

	for (unsigned int i = 0; i < 100; i++) {
		age::Sprite* sprite = new age::Sprite();
		float x = posDist(mt);
		float y = posDist(mt);
		float width = dimDist(mt) / 3.0f;
		float height = dimDist(mt) / 3.0f;

		sprite->init(x, y, width, height);
		m_sprites.push_back(sprite);
	}
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

	m_basicShaderProgram.bind();
	m_time += 0.03f;

	m_basicShaderProgram.setUniform("time", m_time);
	for (auto sprite : m_sprites) {
		sprite->draw();
	}
	m_basicShaderProgram.unbind();
}

void MyTestGame::onExit() {}
