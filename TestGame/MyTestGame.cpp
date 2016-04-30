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

#include <Box2D/Box2D.h>

MyTestGame::MyTestGame() : age::Game("My First Test Game") {
    age::Box2DPhysicsEngine* physicsEngine = new age::Box2DPhysicsEngine();
    physicsEngine->init(glm::vec2(0.0f, -18.0f));
    setPhysicsEngine(physicsEngine);
}

MyTestGame::~MyTestGame() {}


void MyTestGame::onInit() {
    
    age::Music* music = age::AudioEngine::instance().loadMusic("heroic.mp3");
    music->play();
    
    m_sound = age::AudioEngine::instance().loadSound("IceShatters/LedasLuzta2.ogg");
    
    // Init Shader Program
    m_basicShader.init();
    
    m_camera.init(800, 600);
    
    age::Texture* brickTexture = age::ResourceManager::instance().loadTexture("mario-brick.png");
    //age::Texture* brickTexture = age::ResourceManager::instance().loadTexture("test.png");
    age::Texture* metalTexture = age::ResourceManager::instance().loadTexture("metal-texture.png");
    age::Texture* woodTexture = age::ResourceManager::instance().loadTexture("wood-texture.png");
    
    
    
    m_scenePhysicsEngine = new age::Box2DPhysicsEngine();
    glm::vec2 gravity(0.0f, -14.0f);
    {
        m_sceneLayer = new age::Layer();
        m_scenePhysicsEngine->init(gravity);
        m_sceneLayer->setPhysicsEngine(m_scenePhysicsEngine);
        
        // Cube
        glm::vec2 pos(260.0f, 400.0f);
        float width = 40.0f;
        float height = 40.0f;
        m_cubeGO = m_sceneLayer->createGameObject();
        m_cubeGO->setPosition(pos);
        
        age::SpriteComponent* brickSpriteComp = new age::SpriteComponent(width, height);
        brickSpriteComp->setTexture(metalTexture);
        m_cubeGO->addComponent(brickSpriteComp);
        
        age::RigidBodyComponent* cubeRBC = m_cubeGO->createRigidBodyComponent(IRigidBody::Type::DYNAMIC,
                                                                          pos, width, height);
        cubeRBC->setPhysicsParams(2.0f, 2.0f, 0.6f);
        m_cubeGO->addComponent(cubeRBC);
        
        // Tile
        glm::vec2 tilePos = glm::vec2(200, 20);
        glm::vec2 tileDims = glm::vec2(400, 40);
        age::GameObject* tileGO = m_sceneLayer->createGameObject();
        tileGO->setPosition(tilePos);
        
        age::TileComponent* tileComp = new age::TileComponent(tileDims.x, tileDims.y, 5);
        tileComp->setTexture(brickTexture);
        tileGO->addComponent(tileComp);
        
        age::RigidBodyComponent* tileRBC = tileGO->createRigidBodyComponent(IRigidBody::Type::STATIC,
                                                                            tilePos, tileDims.x, tileDims.y);
        tileRBC->setPhysicsParams(1.0f, 3.0f, 0.4f);
        tileGO->addComponent(tileRBC);
    }
    
    /*
    
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
    unsigned int nbSpritesX = 15;
    unsigned int nbSpritesY = 15;
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
    
    m_player = new age::AnimatedSprite("spelunky-sprite-sheet.png", 13, 13);
    m_player->init(200, 200, 90, 80);
    age::Animation2D* idleAnimation = new age::Animation2D(52, 3, 350);
    m_player->addAnimation("idle", idleAnimation);
    age::Animation2D* walkAnimation = new age::Animation2D(156, 9, 500);
    m_player->addAnimation("walk", walkAnimation);
    */
    m_batchRenderer.init();
}

void MyTestGame::onInput(SDL_Event evt) {
    /*
    float currentCameraScale = m_camera.getScale();
    float cameraSpeed = 8.0f;
    float speed = 0.01f;
    
    if (m_inputManager.isKeyPressed(SDLK_SPACE)) {
        m_sound->play();
    }
    
    if (m_inputManager.isKeyPressed(SDLK_a)) {
        m_camera.setScale(currentCameraScale + 0.01f);
    }
    else if (m_inputManager.isKeyPressed(SDLK_q)) {
        m_camera.setScale(currentCameraScale - 0.01f);
    }
    
    if (m_inputManager.isKeyPressed(SDLK_LEFT)) {
        if (m_playerVelocity > -1.0f) {
            m_playerVelocity -= speed;
        }
    }
    else if (m_inputManager.isKeyPressed(SDLK_RIGHT)) {
        if (m_playerVelocity < 1.0f) {
            m_playerVelocity += speed;
        }
    }
    else {
        m_playerVelocity *= 0.9f;
    }
     */
}

namespace  {
    static const float PI = 3.14159265359f;
}

void MyTestGame::onUpdate(unsigned int deltaTime) {
    
    /*
     age::Texture* metalTexture = age::ResourceManager::instance().loadTexture("metal-texture.png");
     m_dynamicSprites.push_back(new age::Sprite());
     m_dynamicSprites.back()->init(300, 500, 10, 10);
     m_dynamicSprites.back()->setTexture(metalTexture);
     m_dynamicSprites.back()->setColor(age::Color());
     m_dynamicSprites.back()->setRigidBody(m_physicsEngine, IRigidBody::Type::DYNAMIC, 1.0, 0.1, 0.5);
     */
    
    //float angle = m_testGO->getAngle() + 0.015f;
    //if (angle > 2 * PI) angle = 0.0f;
    //m_testGO->setAngle(angle);
    m_sceneLayer->update(deltaTime);
    /*
    for(auto sprite : m_dynamicSprites) {
        sprite->updateFromPhysics();
    }
    
    
    glm::vec2 playerPos = m_player->getPosition();
    m_player->setPosition(playerPos + glm::vec2(m_playerVelocity * deltaTime, 0.0f));
    
    if (m_playerVelocity > 0.05f) {
        m_player->playAnimation("walk", deltaTime);
    }
    else if (m_playerVelocity < -0.05f) {
        m_player->playAnimation("walk", deltaTime, true);
    }
    else {
        m_player->playAnimation("idle", deltaTime);
    }
    */
    m_camera.update();
}

void MyTestGame::onRender() {
    
    m_basicShader.bind();
    m_basicShader.setProjectionMatrix(m_camera.getProjection());
    
    
    m_batchRenderer.begin();
    m_sceneLayer->render(&m_batchRenderer);
    /*
    for(auto sprite : m_backgroundSprites) {
        m_batchRenderer.submit(sprite);
    }
    for(auto sprite : m_containerSprites) {
        m_batchRenderer.submit(sprite);
    }
    for(auto sprite : m_dynamicSprites) {
        m_batchRenderer.submit(sprite);
    }
    m_batchRenderer.submit(m_player);
     */
    m_batchRenderer.end();
    m_batchRenderer.render();
    
    m_basicShader.unbind();
}

void MyTestGame::onExit() {}
