#include "stdafx.h"

#include "MyTestGame.h"


MyTestGame::MyTestGame() : age::Game("Test Game") {}
MyTestGame::~MyTestGame() {}

void MyTestGame::onInit() {}

void MyTestGame::onInput(SDL_Event evt) {}

void MyTestGame::onUpdate(unsigned int deltaTime) {}

void MyTestGame::onRender() {}

void MyTestGame::onExit() {}
