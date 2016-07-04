#include "MainMenu.h"

#include <random>
#include <glm/gtx/rotate_vector.hpp>

#include <SDL2/SDL.h>
#include <core/ResourceManager.h>
#include <input/InputManager.h>
#include <core/Game.h>


std::string MainMenu::getNext() const {
    return "Level1";
}

void MainMenu::onInit() {
    
    // Init Shader Program
    m_basicShader.init();
    
    m_camera.init(800, 600);
    m_camera.setPos(400, 300);
    m_camera.setScale(0.6f);

    // Particule engine setup
    m_particuleTexture = age::ResourceManager::instance().loadTexture("fadedCircle.png");
    m_particuleEngine = new age::ParticleEngine2D();
    m_particuleBatch = m_particuleEngine->createParticuleBatch(6000, m_particuleTexture->getId(), 0.001f,
                                                                     [](age::Particle2D& particule, float deltaTime) {
                                                                         particule.position += particule.velocity * deltaTime;
                                                                         particule.color.a = static_cast<GLubyte>(particule.life * 255.0f);
                                                                     });
    m_batchRenderer.init();
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
}

void MainMenu::onUpdate(float deltaTime) {
    m_particuleEngine->update(deltaTime);

    // Random engine init
    static std::mt19937 randomGenerator(static_cast<unsigned int>(time(nullptr)));
    static std::uniform_real_distribution<float> randomAngle(0.0f, 180.0f);
    static std::uniform_int_distribution<int> randomX(20, 650);
    static std::uniform_int_distribution<unsigned char> randomColor(80, 255);

    unsigned char red = randomColor(randomGenerator);
    unsigned char green = randomColor(randomGenerator);
    unsigned char blue = randomColor(randomGenerator);
    unsigned int color = (red << 24) + (green << 16) + (blue << 8) + 0xFF;
    age::Color particuleColor(color);

    
    for(int i = 0; i < 100; i++) {
        int x = randomX(randomGenerator);
        int y = randomX(randomGenerator);
        glm::vec2 velocity = glm::vec2(0.005f, 0.2f);
        velocity = glm::rotate(velocity, randomAngle(randomGenerator));
        
        m_particuleBatch->addParticle(glm::vec2(x + i, y + i),
                                        10, velocity, particuleColor);
    }
    m_camera.update();
}

void MainMenu::onRender() {
    m_basicShader.bind();
    m_basicShader.setProjectionMatrix(m_camera.getProjection());
    
    m_batchRenderer.begin();
    
    m_particuleEngine->render(m_batchRenderer);
    
    m_batchRenderer.end();
    m_batchRenderer.render();
    
    m_basicShader.unbind();
}
