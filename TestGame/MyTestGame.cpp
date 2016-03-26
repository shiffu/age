#include "stdafx.h"

#include "MyTestGame.h"

#include <iostream>
#include <random>

#include <Utils.h>
#include <Sprite.h>
#include <ResourceManager.h>
#include <Box2DPhysicsEngine.h>

#include <Box2D/Box2D.h>

MyTestGame::MyTestGame() : age::Game("My First Test Game") {
    age::Box2DPhysicsEngine* physicsEngine = new age::Box2DPhysicsEngine();
    physicsEngine->init(glm::vec2(0.0f, -18.0f));
    setPhysicsEngine(physicsEngine);
}

MyTestGame::~MyTestGame() {}


void MyTestGame::onInit() {
    
    //glEnable(GL_TEXTURE_2D);        // TODO: Needed??

	// Init Shader Program
	// TODO: Do not hardcode the path to resources (resourceManager)
    m_basicShaderProgram.compileShaders("../age/shaders/basic");

    m_basicShaderProgram.bindAttribute("position");
    m_basicShaderProgram.bindAttribute("color");
    m_basicShaderProgram.bindAttribute("uv");

    m_basicShaderProgram.linkProgram();

	m_camera.init(800, 600);
    
    age::Texture* brickTexture = age::ResourceManager::instance().loadTexture("mario-brick.png");
    age::Texture* woodTexture = age::ResourceManager::instance().loadTexture("wood-texture.png");
    age::Texture* metalTexture = age::ResourceManager::instance().loadTexture("metal-texture.png");

    m_groundSprite = new age::Sprite();
    m_groundSprite->init(40, 30, 550, 60);
    m_groundSprite->setTexture(woodTexture);
    m_groundSprite->setRigidBody(m_physicsEngine, IRigidBody::Type::STATIC, 0, 0.3, 0.1);
    
    m_cubeSprite = new age::Sprite();
    m_cubeSprite->init(60.0, 400.0, 60.0f, 60.0f);
    m_cubeSprite->setTexture(metalTexture);
    m_cubeSprite->setRigidBody(m_physicsEngine, IRigidBody::Type::DYNAMIC, 1.0, 0.25, 0.5);
    
    age::Color colorSprite;
    for(int i = 0; i < NB_DYN_SPRITES; i++) {
        m_dynamicSprites.push_back(new age::Sprite());
        m_dynamicSprites.back()->init(260 + i * 12, 400 + i * 10, 15 + i, 15 + i);
        m_dynamicSprites.back()->setTexture(metalTexture);
        colorSprite.r = 30 * i * 5;
        colorSprite.g = 30 * i * 5;
        colorSprite.b = 30 + i * 5;
        m_dynamicSprites.back()->setColor(colorSprite);
        m_dynamicSprites.back()->setRigidBody(m_physicsEngine, IRigidBody::Type::DYNAMIC, 1.0, 0.1, 0.5);
    }
    
    // Test BatchRenderer2D
    unsigned int nbSpritesX = 10;
    unsigned int nbSpritesY = 10;
    float width = 800.0f / nbSpritesX;
    float height = 600.0f / nbSpritesY;

    age::Color color;
    age::Sprite* sprite = nullptr;
    for(int i =  0; i < nbSpritesX; i++) {
        for(int j =  0; j < nbSpritesY; j++) {
            sprite = new age::Sprite();
            sprite->init(i * width, j * height, width-2, height-2);
            color.r = (255/nbSpritesX) * j;
            color.g = (255/nbSpritesY) * j;
            color.b = (255/nbSpritesX) * j;
            sprite->setColor(color);
            sprite->setTexture(brickTexture);
            m_sprites.push_back(sprite);
        }
    }
    
    m_batchRenderer.init();
}

void MyTestGame::onInput(SDL_Event evt) {
    /*
    float speed = 3.0f;
     
	if (m_inputManager.isKeyPressed(SDLK_LEFT)) {
        glm::vec2 currentPos = m_cubeSprite->getPosition();
		m_cubeSprite->setPosition(currentPos.x - speed, currentPos.y);
	}

	if (m_inputManager.isKeyPressed(SDLK_RIGHT)) {
		glm::vec2 currentPos = m_cubeSprite->getPosition();
		m_cubeSprite->setPosition(currentPos.x + speed, currentPos.y);
	}

	if (m_inputManager.isKeyPressed(SDLK_UP)) {
		glm::vec2 currentPos = m_cubeSprite->getPosition();
		m_cubeSprite->setPosition(currentPos.x, currentPos.y + speed);
	}

	if (m_inputManager.isKeyPressed(SDLK_DOWN)) {
		glm::vec2 currentPos = m_cubeSprite->getPosition();
		m_cubeSprite->setPosition(currentPos.x, currentPos.y - speed);
	}
     */
}

void MyTestGame::onUpdate() {
    m_cubeSprite->updateFromPhysics();
    for(auto sprite : m_dynamicSprites) {
        sprite->updateFromPhysics();
    }
    
    m_camera.update();
}

void MyTestGame::onRender() {

	m_basicShaderProgram.bind();

	m_basicShaderProgram.setUniform("projection", m_camera.getProjection());
    // set the texture unit
    m_basicShaderProgram.setUniform("texSampler", 0);

    m_batchRenderer.begin(age::RenderingSortType::NONE);
    for(auto sprite : m_sprites) {
        m_batchRenderer.submit(sprite);
    }
    m_batchRenderer.submit(m_groundSprite);
    m_batchRenderer.submit(m_cubeSprite);
    for(auto sprite : m_dynamicSprites) {
        m_batchRenderer.submit(sprite);
    }
    m_batchRenderer.end();
    
    m_batchRenderer.render();
    
	m_basicShaderProgram.unbind();
}

void MyTestGame::onExit() {}
