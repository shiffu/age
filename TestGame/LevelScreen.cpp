#include "LevelScreen.h"


#include <random>
#include <glm/gtx/rotate_vector.hpp>

#include <core/Utils.h>
#include <core/ResourceManager.h>
#include <physics/Box2DPhysicsEngine.h>
#include <core/GameObject.h>
#include <core/SpriteComponent.h>
#include <core/RigidBodyComponent.h>
#include <rendering/TextureAtlas.h>
#include <rendering/Animator.h>
#include <rendering/Animation2D.h>
#include <rendering/Sprite.h>


LevelScreen::LevelScreen(unsigned int level) : m_level(level) {}
LevelScreen::~LevelScreen() {}


std::string LevelScreen::getNext() const {
    return "MainMenu";
}

void LevelScreen::onInit() {
    // cdk_Like_Music.mp3
    // grapes_dunno.mp3
    // heroic.mp3
    m_music = age::AudioEngine::instance().loadMusic("grapes_dunno.mp3");
    m_sound = age::AudioEngine::instance().loadSound("IceShatters/LedasLuzta2.ogg");
    
    // Init Shader Program
    m_basicShader.init();
    
    m_camera.init(400, 300);
    m_camera.setPos(400, 300);
    m_camera.setScale(0.5f);
    
    m_brickTexture = age::ResourceManager::instance().loadTexture("mario-brick.png");
    m_metalTexture = age::ResourceManager::instance().loadTexture("metal-texture.png");
    m_particuleTexture = age::ResourceManager::instance().loadTexture("fadedCircle.png");
    
    m_sceneLayer = new age::Layer();
    
    // Cube
    float width = 60.0f;
    float height = 60.0f;
    m_cubeGO = m_sceneLayer->createGameObject();
    
    age::Sprite* cubeSprite = new age::Sprite(width, height);
    age::SpriteComponent* cubeSpriteComp = new age::SpriteComponent(cubeSprite);
    cubeSprite->setTexture(m_metalTexture);
    m_cubeGO->addComponent(cubeSpriteComp);
    
    // Ground
    glm::vec2 groundDims = glm::vec2(1600, 40);
    m_groundGO = m_sceneLayer->createGameObject();
    
    age::SpriteComponent* groundComp = new age::SpriteComponent(groundDims.x, groundDims.y, 40);
    groundComp->setTexture(m_brickTexture);
    m_groundGO->addComponent(groundComp);
    
    // Player
    glm::vec2 playerDims = glm::vec2(40, 42);
    m_player = m_sceneLayer->createGameObject();
    
    age::SpriteComponent* playerSpriteComp = new age::SpriteComponent(playerDims.x, playerDims.y);
    age::Texture* playerTextureSheet = age::ResourceManager::instance().loadTexture("mygame-sheet.png");
    playerSpriteComp->setTexture(playerTextureSheet);
    
    m_playerAnimator = new age::Animator(new age::TextureAtlas(playerTextureSheet, 64, 64));
    m_playerAnimator->addAnimation("idle", new age::Animation2D(0, 7, 620));
    m_playerAnimator->addAnimation("walk", new age::Animation2D(8, 9, 820));
    
    playerSpriteComp->setAnimator(m_playerAnimator);
    m_player->addComponent(playerSpriteComp);
    
    // Particule engine setup
    m_particuleEngine = new age::ParticleEngine2D();
    m_playerParticuleBatch = m_particuleEngine->createParticuleBatch(100, m_particuleTexture, 0.0025f,
                                                     [](age::Particle2D& particule, float deltaTime) {
                                                         particule.position += particule.velocity * deltaTime;
                                                         particule.color.a = static_cast<GLubyte>(particule.life * 255.0f);
                                                     });
    
    m_batchRenderer.init();
    
    m_testSprite.setPosition(glm::vec2(80, 500));
    m_testSprite.setColor(age::Color(0x00FFFFFF));
}

void LevelScreen::onExit() {
    m_music->stop();
    m_sceneLayer->destroyPhysicsEngine();
}

void LevelScreen::onDestroy() {
}

void LevelScreen::onEntry() {
    m_gameOver = false;
    m_music->play();

    // Setup the Physics
    glm::vec2 gravity(0.0f, -14.0f);
    m_scenePhysicsEngine = new age::Box2DPhysicsEngine();
    m_scenePhysicsEngine->init(gravity);
    m_sceneLayer->setPhysicsEngine(m_scenePhysicsEngine);

    // Cube
    glm::vec2 pos(200.0f, 500.0f);
    float width = 60.0f;
    float height = 60.0f;
    age::RigidBodyComponent* cubeRBC = m_cubeGO->createRigidBodyComponent(age::IRigidBody::Type::DYNAMIC, pos);
    age::Collider* cubeCollider = new age::Collider(age::PhysicsDef(1.0f, 0.7f, 0.4f), age::BoxDef(width, height));
    cubeCollider->addLabel("cube");
    cubeRBC->getRigidBody()->addCollider("cube", cubeCollider);
    
    // Ground
    glm::vec2 groundPos = glm::vec2(400, 20);
    glm::vec2 groundDims = glm::vec2(1600, 40);
    
    age::RigidBodyComponent* groundRBC = m_groundGO->createRigidBodyComponent(age::IRigidBody::Type::STATIC, groundPos);
    age::Collider* groundCollider = new age::Collider(age::PhysicsDef(1.0f, 0.2f, 0.1f), age::BoxDef(groundDims.x, groundDims.y));
    groundCollider->addLabel("ground");
    groundRBC->getRigidBody()->addCollider("ground", groundCollider);
    
    // Player
    glm::vec2 playerPos = glm::vec2(200, 61);
    glm::vec2 playerDims = glm::vec2(40, 42);
    
    age::RigidBodyComponent* playerRBC = m_player->createRigidBodyComponent(age::IRigidBody::Type::DYNAMIC, playerPos);
    playerRBC->getRigidBody()->setFixedRotation(true);
    
    age::PhysicsDef playerPhysicsDef(1.0f, 0.3f, 0);
    age::Collider* playerCollider = new age::Collider(playerPhysicsDef, age::BoxDef(playerDims.x, playerDims.y));
    playerRBC->getRigidBody()->addCollider("playerMain", playerCollider);
    age::Collider* playerFeetCollider = new age::Collider(playerPhysicsDef, age::BoxDef(glm::vec2(0, -21), 12, 2), true);
    playerFeetCollider->addLabel("playerFeet");
    playerFeetCollider->setCollisionAware(true);
    playerRBC->getRigidBody()->addCollider("playerFeet", playerFeetCollider);
}

void LevelScreen::onInput() {
    const age::InputManager* inputManager = getGame()->getInputManager();
    if (inputManager->isKeyPressed(SDLK_ESCAPE)) {
        m_gameOver = true;
        setState(age::ScreenState::GO_NEXT);
        return;
    }

    // Camera
    float currentCameraScale = m_camera.getScale();
    
    if (inputManager->isKeyPressed(SDLK_a)) {
        m_camera.setScale(currentCameraScale + 0.004f);
    }
    else if (inputManager->isKeyPressed(SDLK_q)) {
        m_camera.setScale(currentCameraScale - 0.004f);
    }
    
    // Player
    float xForceMagnitude = 18.0f;
    float yForceMagnitude = 10.0f;
    float maxSpeed = 3.5f;
    age::RigidBodyComponent* playerRBC = m_player->getComponent<age::RigidBodyComponent>();
    age::Color particuleColor(0xFFEEEEFF);
    
    // Random engine init
    static std::mt19937 randomGenerator(static_cast<unsigned int>(time(nullptr)));
    static std::uniform_real_distribution<float> randomAngle(0.0f, 3.14159265f * 2.0f);
    
    if (playerRBC) {
        
        if (inputManager->isKeyPressed(SDLK_SPACE)
            && playerRBC->getRigidBody()->getCollider("playerFeet")->isTouchingAny({"ground", "cube"})) {
            
            if (m_jumpThreshold == 0) {
                m_jumpThreshold = 2;
                m_sound->play();
                playerRBC->getRigidBody()->applyLinearImpulse(glm::vec2(0, yForceMagnitude));
                
                // Add particules
                for(int i = 0; i < 30; i++) {
                    glm::vec2 velocity = glm::vec2(0.001f, -0.055f);
                    velocity = glm::rotate(velocity, randomAngle(randomGenerator));
                    
                    m_playerParticuleBatch->addParticle(m_player->getPosition() + glm::vec2(i * 1.2f, -22.0f),
                                                        10, velocity, particuleColor);
                }
            }
            else {
                m_jumpThreshold--;
            }
        }
        
        if (inputManager->isKeyPressed(SDLK_LEFT) && playerRBC->getRigidBody()->getVelocity().x > -maxSpeed) {
            playerRBC->getRigidBody()->applyForce(glm::vec2(-xForceMagnitude, 0));
        }
        else if (inputManager->isKeyPressed(SDLK_RIGHT) && playerRBC->getRigidBody()->getVelocity().x < maxSpeed) {
            playerRBC->getRigidBody()->applyForce(glm::vec2(xForceMagnitude, 0));
        }
        else {
            playerRBC->getRigidBody()->applyForce(glm::vec2(0, 0));
        }
    }
}

void LevelScreen::onUpdate(float deltaTime) {
    m_sceneLayer->update(deltaTime);
    m_particuleEngine->update(deltaTime);
    
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

void LevelScreen::onRender() {
    m_basicShader.bind();
    m_basicShader.setProjectionMatrix(m_camera.getProjection());
    
    m_batchRenderer.begin();
    
    m_sceneLayer->render(&m_batchRenderer);
    m_particuleEngine->render(m_batchRenderer);
    
    m_testSprite.draw(&m_batchRenderer);
    
    m_batchRenderer.end();
    m_batchRenderer.render();
    
    m_basicShader.unbind();    
}
