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

    age::Sprite* cSprite = new age::Sprite();
    cSprite->init(40, 30, 550, 60);
    cSprite->setTexture(woodTexture);
    cSprite->setRigidBody(m_physicsEngine, IRigidBody::Type::STATIC, 0, 0.3, 0.1);
    m_containerSprites.push_back(cSprite);
    
    cSprite = new age::Sprite();
    cSprite->init(40, 30, 40, 150);
    cSprite->setTexture(woodTexture);
    cSprite->setRigidBody(m_physicsEngine, IRigidBody::Type::STATIC, 0, 0.3, 0.1);
    m_containerSprites.push_back(cSprite);
    
    cSprite = new age::Sprite();
    cSprite->init(590, 30, 40, 150);
    cSprite->setTexture(woodTexture);
    cSprite->setRigidBody(m_physicsEngine, IRigidBody::Type::STATIC, 0, 0.3, 0.1);
    m_containerSprites.push_back(cSprite);
    
    age::Color colorSprite;
    for(int i = 0; i < NB_DYN_SPRITES; i++) {
        m_dynamicSprites.push_back(new age::Sprite());
        m_dynamicSprites.back()->init(220 + i * 2, 450 + i * 2, 12 + i/5, 12 + i/5);
        m_dynamicSprites.back()->setTexture(metalTexture);
        colorSprite.r = 80 + i * 2;
        colorSprite.g = 80 + i * 2;
        colorSprite.b = 80 + i * 2;
        m_dynamicSprites.back()->setColor(colorSprite);
        m_dynamicSprites.back()->setRigidBody(m_physicsEngine, IRigidBody::Type::DYNAMIC, 1.0, 0.1, 0.5);
    }
    
    // Test BatchRenderer2D
    unsigned int nbSpritesX = 25;
    unsigned int nbSpritesY = 25;
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
            m_backgroundSprites.push_back(sprite);
        }
    }
    
    m_batchRenderer.init();
}

void MyTestGame::onInput(SDL_Event evt) {
    glm::vec2 currentCameraPos = m_camera.getPos();
    float currentCameraScale = m_camera.getScale();
    float cameraSpeed = 8.0f;
    
    if (m_inputManager.isKeyPressed(SDLK_a)) {
        m_camera.setScale(currentCameraScale + 0.01f);
    }
    else if (m_inputManager.isKeyPressed(SDLK_q)) {
        m_camera.setScale(currentCameraScale - 0.01f);
    }
    
    if (m_inputManager.isKeyPressed(SDLK_LEFT)) {
        m_camera.setPos(currentCameraPos + glm::vec2(-cameraSpeed, 0.0f));
    }
    else if (m_inputManager.isKeyPressed(SDLK_RIGHT)) {
        m_camera.setPos(currentCameraPos + glm::vec2(cameraSpeed, 0.0f));
    }

	if (m_inputManager.isKeyPressed(SDLK_UP)) {
        m_camera.setPos(currentCameraPos + glm::vec2(0.0f, cameraSpeed));
	}
	else if (m_inputManager.isKeyPressed(SDLK_DOWN)) {
        m_camera.setPos(currentCameraPos + glm::vec2(0.0f, -cameraSpeed));
	}
}

void MyTestGame::onUpdate() {
    
    /*
    age::Texture* metalTexture = age::ResourceManager::instance().loadTexture("metal-texture.png");
    m_dynamicSprites.push_back(new age::Sprite());
    m_dynamicSprites.back()->init(300, 500, 10, 10);
    m_dynamicSprites.back()->setTexture(metalTexture);
    m_dynamicSprites.back()->setColor(age::Color());
    m_dynamicSprites.back()->setRigidBody(m_physicsEngine, IRigidBody::Type::DYNAMIC, 1.0, 0.1, 0.5);
     */

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

    //m_batchRenderer.begin(age::RenderingSortType::NONE);
    m_batchRenderer.begin();
        for(auto sprite : m_backgroundSprites) {
            m_batchRenderer.submit(sprite);
        }
        for(auto sprite : m_containerSprites) {
            m_batchRenderer.submit(sprite);
        }
        for(auto sprite : m_dynamicSprites) {
            m_batchRenderer.submit(sprite);
        }
    m_batchRenderer.end();
    m_batchRenderer.render();
    
	m_basicShaderProgram.unbind();
}

void MyTestGame::onExit() {}
