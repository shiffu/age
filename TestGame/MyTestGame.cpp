#include "stdafx.h"

#include "MyTestGame.h"

#include <iostream>
#include <random>

#include <Utils.h>
#include <Sprite.h>
#include <ResourceManager.h>
#include <Box2D/Box2D.h>

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

    m_basicShaderProgram.bindAttribute("position");
    m_basicShaderProgram.bindAttribute("color");
    m_basicShaderProgram.bindAttribute("uv");

    m_basicShaderProgram.linkProgram();

	m_camera.init(800, 600);

    /*
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> posDist(0, 200);
	std::uniform_real_distribution<float> dimDist(100, 450);
     */

	//for (unsigned int i = 0; i < 20; i++) {
	//	age::Sprite* sprite = new age::Sprite();
	//	float x = posDist(mt);
	//	float y = posDist(mt);
	//	float width = dimDist(mt);
	//	float height = dimDist(mt);

	//	sprite->init(x, y, width, height);
	//	m_sprites.push_back(sprite);
	//}
    
    
    
    // Box2D Init
    // World first
    if (m_world == nullptr) {
        b2Vec2 gravity(0.0f, -15.0f);
        m_world = new b2World(gravity);
    }
    // Define ground body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(30.0f, 0.0f);
    b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
    
    // Define the ground shape
    b2PolygonShape groundBox;
    groundBox.SetAsBox(30.0f, 0.5f);
    
    // Define the ground Fixture
    groundBody->CreateFixture(&groundBox, 0.0f);
    
    // Dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(4.0f, 20.0f);
    m_body = m_world->CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(2.0f, 2.0f);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 3.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.55f;
    m_body->CreateFixture(&fixtureDef);
    

    
    age::Texture* texture = age::ResourceManager::instance().loadTexture("mario-brick.png");
    age::Sprite* sprite = nullptr;

    
    m_cubeSprite = new age::Sprite();
    m_cubeSprite->init(4.0 * W2P, 20.0 * W2P, 2 * W2P, 2 * W2P);
    m_cubeSprite->setTexture(texture);
    

    
    // Test BatchRenderer2D
    unsigned int nbSpritesX = 40;
    unsigned int nbSpritesY = 40;
    float width = 800.0f / nbSpritesX;
    float height = 600.0f / nbSpritesY;

    for(int i =  0; i < nbSpritesX; i++) {
        for(int j =  0; j < nbSpritesY; j++) {
            sprite = new age::Sprite();
            sprite->init(i * width, j * height, width-2, height-2);
            age::Color color;
            color.rgba.r = (255/nbSpritesX) * i;
            color.rgba.g = (255/nbSpritesY) * j;
            color.rgba.b = (255/nbSpritesX) * i;
            color.rgba.a = 255;
            sprite->setColor(color);
            sprite->setTexture(texture);
            m_sprites.push_back(sprite);
        }
    }
    
    m_batchRenderer.init();
}

void MyTestGame::onInput(SDL_Event evt) {
	float speed = 2.0f;

	if (m_inputManager.isKeyPressed(SDLK_a)) {
		age::Position2D currentPos = m_sprites.back()->getPosition();
		m_sprites.back()->setPosition(currentPos.x - speed, currentPos.y);
	}

	if (m_inputManager.isKeyPressed(SDLK_d)) {
		age::Position2D currentPos = m_sprites.back()->getPosition();
		m_sprites.back()->setPosition(currentPos.x + speed, currentPos.y);
	}

	if (m_inputManager.isKeyPressed(SDLK_w)) {
		age::Position2D currentPos = m_sprites.back()->getPosition();
		m_sprites.back()->setPosition(currentPos.x, currentPos.y + speed);
	}

	if (m_inputManager.isKeyPressed(SDLK_s)) {
		age::Position2D currentPos = m_sprites.back()->getPosition();
		m_sprites.back()->setPosition(currentPos.x, currentPos.y - speed);
	}
}

void MyTestGame::onUpdate() {
    m_camera.update();
}

void MyTestGame::onRender() {

    
    // Update the physics engine
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    
    m_world->Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = m_body->GetPosition();
    float32 angle = m_body->GetAngle();
    //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    m_cubeSprite->setPosition(position.x * W2P, position.y * W2P);

    
    
	m_basicShaderProgram.bind();

	m_basicShaderProgram.setUniform("projection", m_camera.getProjection());
	m_basicShaderProgram.setUniform("texSampler", 0);

    m_batchRenderer.begin();
    for(auto sprite : m_sprites) {
        m_batchRenderer.submit(sprite);
    }
    m_batchRenderer.submit(m_cubeSprite);
    m_batchRenderer.end();
    
    m_batchRenderer.render();
    
	m_basicShaderProgram.unbind();
}

void MyTestGame::onExit() {}
