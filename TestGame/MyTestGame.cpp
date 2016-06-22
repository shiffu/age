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
    //age::Texture* woodTexture = age::ResourceManager::instance().loadTexture("wood-texture.png");
    
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
        
    age::RigidBodyComponent* cubeRBC = m_cubeGO->createRigidBodyComponent(age::IRigidBody::Type::DYNAMIC, pos);
    age::Collider* cubeCollider = new age::Collider(age::PhysicsDef(1.0f, 0.2f, 0.4f), age::BoxDef(width, height));
    cubeRBC->getRigidBody()->addCollider(cubeCollider);
        
    // Tile
    glm::vec2 tilePos = glm::vec2(400, 20);
    glm::vec2 tileDims = glm::vec2(800, 40);
    age::GameObject* tileGO = m_sceneLayer->createGameObject();
    tileGO->setPosition(tilePos);
        
    age::TileComponent* tileComp = new age::TileComponent(tileDims.x, tileDims.y, 20);
    tileComp->setTexture(brickTexture);
    tileGO->addComponent(tileComp);

    age::RigidBodyComponent* tileRBC = tileGO->createRigidBodyComponent(age::IRigidBody::Type::STATIC, tilePos);
    /*age::Collider* */m_tileCollider = new age::Collider(age::PhysicsDef(1.0f, 3.0f, 0.4f), age::BoxDef(tileDims.x, tileDims.y));
    tileRBC->getRigidBody()->addCollider(m_tileCollider);

	// Player
	glm::vec2 playerPos = glm::vec2(20, 61);
	glm::vec2 playerDims = glm::vec2(40, 42);
	m_player = m_sceneLayer->createGameObject();
	m_player->setPosition(playerPos);

	age::SpriteComponent* playerSpriteComp = new age::SpriteComponent(playerDims.x, playerDims.y);
	age::Texture* playerTextureSheet = age::ResourceManager::instance().loadTexture("mygame-sheet.png");
	playerSpriteComp->setTexture(playerTextureSheet);

	m_playerAnimator = new age::Animator(new age::TextureAtlas(playerTextureSheet, 64, 64));
	m_playerAnimator->addAnimation("idle", new age::Animation2D(0, 7, 620));
	m_playerAnimator->addAnimation("walk", new age::Animation2D(8, 9, 820));

	playerSpriteComp->setAnimator(m_playerAnimator);
	m_player->addComponent(playerSpriteComp);

	age::RigidBodyComponent* playerRBC = m_player->createRigidBodyComponent(age::IRigidBody::Type::DYNAMIC, playerPos);
    playerRBC->getRigidBody()->setFixedRotation(true);

    age::Collider* playerCollider = new age::Collider(age::PhysicsDef(1.2f, 0.6f, 0.001f), age::BoxDef(playerDims.x, playerDims.y));
    playerRBC->getRigidBody()->addCollider(playerCollider);
    /*age::Collider* */m_playerFeetCollider = new age::Collider(age::PhysicsDef(1.2f, 0.6f, 0.001f), age::BoxDef(glm::vec2(20, -20), 20, 5));
    m_playerFeetCollider->setCollisionAware(true);
    playerRBC->getRigidBody()->addCollider(m_playerFeetCollider);

    m_batchRenderer.init();
}

void MyTestGame::onInput(SDL_Event evt) {
	// Camera
    float currentCameraScale = m_camera.getScale();    
    if (m_inputManager.isKeyPressed(SDLK_a)) {
        m_camera.setScale(currentCameraScale + 0.004f);
    }
    else if (m_inputManager.isKeyPressed(SDLK_q)) {
        m_camera.setScale(currentCameraScale - 0.004f);
    }

	// Player
	float xForceMagnitude = 45.0f;
	float yForceMagnitude = 6.0f;
	float maxSpeed = 6.0f;
	age::RigidBodyComponent* playerRBC = m_player->getComponent<age::RigidBodyComponent>();
	if (playerRBC) {

		if (m_inputManager.isKeyPressed(SDLK_SPACE) && m_playerFeetCollider->isTouching(m_tileCollider)) {
			m_sound->play();
			playerRBC->getRigidBody()->applyLinearImpulse(glm::vec2(0, yForceMagnitude));
		}

		if (m_inputManager.isKeyPressed(SDLK_LEFT) && playerRBC->getRigidBody()->getVelocity().x > -maxSpeed) {
			playerRBC->getRigidBody()->applyForce(glm::vec2(-xForceMagnitude, 0));
		}
		else if (m_inputManager.isKeyPressed(SDLK_RIGHT) && playerRBC->getRigidBody()->getVelocity().x < maxSpeed) {
			playerRBC->getRigidBody()->applyForce(glm::vec2(xForceMagnitude, 0));
		}
		else {
			playerRBC->getRigidBody()->applyForce(glm::vec2(0, 0));
		}
	}

}

void MyTestGame::onUpdate(unsigned int deltaTime) {
    
    m_sceneLayer->update(deltaTime);

	// Update the player velocity and animation
	float walkTriggerSpeed = 1.0f;
	age::RigidBodyComponent* playerRBC = m_player->getComponent<age::RigidBodyComponent>();
	if (playerRBC->getRigidBody()->getVelocity().x > walkTriggerSpeed) {
		m_playerFlipped = false;
		m_playerAnimator->playAnimation("walk", deltaTime);
	}
	else if (playerRBC->getRigidBody()->getVelocity().x < -walkTriggerSpeed) {
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
