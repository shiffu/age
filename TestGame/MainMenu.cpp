#include "stdafx.h"

#include "MainMenu.h"

#include <iostream>
#include <random>
#include <glm/gtx/rotate_vector.hpp>

#include <SDL2/SDL.h>
#include <core/ResourceManager.h>
#include <input/InputManager.h>
#include <core/Game.h>
#include <rendering/Square.h>
#include <gui/Theme.h>
#include <gui/Button.h>
#include <gui/Label.h>
#include <audio/AudioEngine.h>


std::string MainMenu::getNext() const {
    if (m_currentMenuItem == MenuItem::START)
        return "Level1";
    
    return "";
}

void MainMenu::onInit() {
    
    // Init Shader Program
    m_basicShader.init();

    m_sound = age::AudioEngine::instance().loadSound("IceShatters/LedasLuzta2.ogg");

    m_camera.init(800, 600);
    //m_camera.init(1024, 960);
    m_camera.setPos(400, 300);
    //m_camera.setScale(0.9f);

    // Particule engine setup
    m_particuleTexture = age::ResourceManager::instance().loadTexture("fadedCircle.png");
    m_particuleEngine = new age::ParticleEngine2D();
    m_particuleBatch = m_particuleEngine->createParticuleBatch(6000, m_particuleTexture, 0.0007f,
                                                                     [](age::Particle2D& particule, float deltaTime) {
                                                                         particule.position += particule.velocity * deltaTime;
                                                                         particule.color.a = static_cast<GLubyte>(particule.life * 255.0f);
                                                                     });
    
    using std::cout;
    m_guiManager.setCamera(&m_camera);
    m_guiManager.setWindow(getGame()->getWindow());
    
    age::Theme* theme = new age::Theme();
	theme->loadFromFile("myTheme.properties");

    m_guiManager.setTheme(theme);
    
    m_startButton = m_guiManager.getButton(glm::vec2(390, 350), glm::vec2(180, 40), "Start");
    m_startButton->setLeftButtonPressedCallback([this](){
        m_sound->play();
        m_currentMenuItem = MenuItem::START;
        setState(age::ScreenState::GO_NEXT);
    });
    age::Label* startLabel = m_startButton->getLabel();
    startLabel->setColor(age::Color(0x307090FF));
    startLabel->setMouseHoverCallback([startLabel] () {
        startLabel->setColor(age::Color(0x102040FF));
    });
    startLabel->setLostFocusCallback([startLabel] () {
        startLabel->setColor(age::Color(0x307090FF));
    });
    
    m_quitButton = m_guiManager.getButton(glm::vec2(390, 300), glm::vec2(180, 40), "Exit");
    m_quitButton->setLeftButtonPressedCallback([this](){
        m_currentMenuItem = MenuItem::QUIT;
        setState(age::ScreenState::GO_NEXT);
    });
    age::Label* quitLabel = m_quitButton->getLabel();
    quitLabel->setColor(age::Color(0xFF1080FF));

    m_batchRenderer.init();
    m_linesBatchRenderer.init();
}

void MainMenu::onExit() {}

void MainMenu::onDestroy() {}

void MainMenu::onEntry() {}

void MainMenu::onInput() {
    const age::InputManager* inputManager = getGame()->getInputManager();
    if (inputManager->isKeyPressed(SDLK_SPACE)) {
        setState(age::ScreenState::GO_NEXT);
        return;
    }
    
    m_guiManager.handleInputs(*inputManager);
}

void MainMenu::onUpdate(float deltaTime) {
    m_particuleEngine->update(deltaTime);

    // Random engine init
    static std::mt19937 randomGenerator(static_cast<unsigned int>(time(nullptr)));
    static std::uniform_real_distribution<float> randomAngle(0.0f, 3.14159265f * 2.0f);
    static std::uniform_int_distribution<int> randomX(5, 750);
    static std::uniform_int_distribution<short> randomColor(60, 255);

    unsigned char red = randomColor(randomGenerator);
    unsigned char green = randomColor(randomGenerator);
    unsigned char blue = randomColor(randomGenerator);
    unsigned int color = (red << 24) + (green << 16) + (blue << 8) + 0xFF;
    age::Color particuleColor(color);

    
    int x = randomX(randomGenerator);
    int y = randomX(randomGenerator);
    for(int i = 0; i < 8; i++) {
        glm::vec2 velocity = glm::vec2(0.01f, 0.2f);
        velocity = glm::rotate(velocity, randomAngle(randomGenerator));
        
        m_particuleBatch->addParticle(glm::vec2(x, y),
                                        6, velocity, particuleColor);
    }
    m_camera.update();
}

void MainMenu::onRender() {
    m_basicShader.bind();
    m_basicShader.setProjectionMatrix(m_camera.getProjection());
    
    m_batchRenderer.begin();
    
    m_particuleEngine->render(m_batchRenderer);
    m_guiManager.render(&m_batchRenderer);
    
    m_batchRenderer.end();
    m_batchRenderer.render();
    
    m_basicShader.unbind();
}
