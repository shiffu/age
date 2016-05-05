#include "stdafx.h"

#include "MyTestGame.h"

#include <iostream>
#include <random>

#include <Utils.h>
#include <ResourceManager.h>
#include <Box2DPhysicsEngine.h>
#include <GameObject.h>
#include <SpriteComponent.h>
#include <TileComponent.h>
#include <RigidBodyComponent.h>
#include <TextureAtlas.h>
#include <Animator.h>
#include <Animation2D.h>


namespace {
	static const float PI = 3.14159265359f;
}

MyTestGame::MyTestGame() : age::Game("My First Test Game") {}
MyTestGame::~MyTestGame() {}

void MyTestGame::onInit() {
    
    age::Music* music = age::AudioEngine::instance().loadMusic("heroic.mp3");
    music->play();
    
    m_sound = age::AudioEngine::instance().loadSound("IceShatters/LedasLuzta2.ogg");
    
    // Init Shader Program
    m_basicShader.init();
    
    m_camera.init(400, 300);
	m_camera.setPos(400, 300);
	m_camera.setScale(0.5f);

    age::Texture* brickTexture = age::ResourceManager::instance().loadTexture("mario-brick.png");
    age::Texture* metalTexture = age::ResourceManager::instance().loadTexture("metal-texture.png");
    age::Texture* woodTexture = age::ResourceManager::instance().loadTexture("wood-texture.png");
    
    m_scenePhysicsEngine = new age::Box2DPhysicsEngine();
    glm::vec2 gravity(0.0f, -14.0f);

    m_sceneLayer = new age::Layer();
    m_scenePhysicsEngine->init(gravity);
    m_sceneLayer->setPhysicsEngine(m_scenePhysicsEngine);
        
    // Cube
    glm::vec2 pos(200.0f, 500.0f);
    float width = 60.0f;
    float height = 60.0f;
    m_cubeGO = m_sceneLayer->createGameObject();
    m_cubeGO->setPosition(pos);
        
    age::SpriteComponent* cubeSpriteComp = new age::SpriteComponent(width, height);
	cubeSpriteComp->setTexture(metalTexture);
    m_cubeGO->addComponent(cubeSpriteComp);
        
    age::RigidBodyComponent* cubeRBC = m_cubeGO->createRigidBodyComponent(IRigidBody::Type::DYNAMIC,
                                                                        pos, width, height);
    cubeRBC->setPhysicsParams(2.0f, 2.0f, 0.6f);
    m_cubeGO->addComponent(cubeRBC);
        
    // Tile
    glm::vec2 tilePos = glm::vec2(400, 20);
    glm::vec2 tileDims = glm::vec2(800, 40);
    age::GameObject* tileGO = m_sceneLayer->createGameObject();
    tileGO->setPosition(tilePos);
        
    age::TileComponent* tileComp = new age::TileComponent(tileDims.x, tileDims.y, 20);
    tileComp->setTexture(brickTexture);
    tileGO->addComponent(tileComp);
        
    age::RigidBodyComponent* tileRBC = tileGO->createRigidBodyComponent(IRigidBody::Type::STATIC,
                                                                        tilePos, tileDims.x, tileDims.y);
    tileRBC->setPhysicsParams(1.0f, 3.0f, 0.4f);
    tileGO->addComponent(tileRBC);

	// Player
	m_player = m_sceneLayer->createGameObject();
	m_player->setPosition(glm::vec2(20.0f, 61.0f));

	age::SpriteComponent* playerSpriteComp = new age::SpriteComponent(40.0f, 42.0f);
	age::Texture* playerTextureSheet = age::ResourceManager::instance().loadTexture("mygame-sheet.png");
	playerSpriteComp->setTexture(playerTextureSheet);

	m_playerAnimator = new age::Animator(new age::TextureAtlas(playerTextureSheet, 64, 64));
	m_playerAnimator->addAnimation("idle", new age::Animation2D(0, 7, 620));
	m_playerAnimator->addAnimation("walk", new age::Animation2D(8, 9, 820));

	playerSpriteComp->setAnimator(m_playerAnimator);
	m_player->addComponent(playerSpriteComp);

    m_batchRenderer.init();
}

void MyTestGame::onInput(SDL_Event evt) {
	// Camera
    float currentCameraScale = m_camera.getScale();
    if (m_inputManager.isKeyPressed(SDLK_SPACE)) {
        m_sound->play();
    }
    
    if (m_inputManager.isKeyPressed(SDLK_a)) {
        m_camera.setScale(currentCameraScale + 0.004f);
    }
    else if (m_inputManager.isKeyPressed(SDLK_q)) {
        m_camera.setScale(currentCameraScale - 0.004f);
    }

	// Player
	float speed = 0.002f;
	if (m_inputManager.isKeyPressed(SDLK_LEFT)) {
        if (m_playerVelocity > -0.1f) {
            m_playerVelocity -= speed;
        }
    }
    else if (m_inputManager.isKeyPressed(SDLK_RIGHT)) {
        if (m_playerVelocity < 0.1f) {
            m_playerVelocity += speed;
        }
    }
    else {
        m_playerVelocity *= 0.95f;
    }
}

void MyTestGame::onUpdate(unsigned int deltaTime) {
    
    m_sceneLayer->update(deltaTime);

	glm::vec2 playerPos = m_player->getPosition();
    m_player->setPosition(playerPos + glm::vec2(m_playerVelocity * deltaTime, 0.0f));
    
	if (m_playerVelocity > 0.02f) {
		m_playerFlipped = false;
		m_playerAnimator->playAnimation("walk", deltaTime);
    }
    else if (m_playerVelocity < -0.02f) {
		m_playerFlipped = true;
		m_playerAnimator->playAnimation("walk", deltaTime, m_playerFlipped);
    }
    else {
		m_playerAnimator->playAnimation("idle", deltaTime, m_playerFlipped);
    }

	// Make the camera follow the player
	age::Camera2D::Constraint followConstraint;
	followConstraint.onlyX = true;
	followConstraint.xMinBoundary = 200;
	m_camera.follow(m_player, &followConstraint);
    m_camera.update();
}

void MyTestGame::onRender() {
    
    m_basicShader.bind();
    m_basicShader.setProjectionMatrix(m_camera.getProjection());    
    
    m_batchRenderer.begin();

	m_sceneLayer->render(&m_batchRenderer);
    
	m_batchRenderer.end();
    m_batchRenderer.render();
    
    m_basicShader.unbind();
}

void MyTestGame::onExit() {}
