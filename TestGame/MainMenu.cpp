#include "MainMenu.h"

#include <random>
#include <glm/gtx/rotate_vector.hpp>

#include <SDL2/SDL.h>
#include <core/ResourceManager.h>
#include <input/InputManager.h>
#include <core/Game.h>
#include <rendering/Square.h>

std::string MainMenu::getNext() const {
    return "Level1";
}

void MainMenu::onInit() {
    
    // Init Shader Program
    m_basicShader.init();
    
    m_camera.init(800, 600);
    m_camera.setPos(400, 300);
    //m_camera.setScale(0.9f);

    // Particule engine setup
    m_particuleTexture = age::ResourceManager::instance().loadTexture("fadedCircle.png");
    m_particuleEngine = new age::ParticleEngine2D();
    m_particuleBatch = m_particuleEngine->createParticuleBatch(8000, m_particuleTexture, 0.0007f,
                                                                     [](age::Particle2D& particule, float deltaTime) {
                                                                         particule.position += particule.velocity * deltaTime;
                                                                         particule.color.a = static_cast<GLubyte>(particule.life * 255.0f);
                                                                     });
    
    //OpenSans-Regular.ttf
    //ENDORALT.ttf
    //calamityJoe.ttf
    //Arial Narrow Bold.ttf
    m_font = new age::SpriteFont("calamityJoe.ttf", 64);
    
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
}

void MainMenu::onUpdate(float deltaTime) {
    m_particuleEngine->update(deltaTime);

    // Random engine init
    static std::mt19937 randomGenerator(static_cast<unsigned int>(time(nullptr)));
    static std::uniform_real_distribution<float> randomAngle(0.0f, 3.14159265f * 2.0f);
    static std::uniform_int_distribution<int> randomX(5, 750);
    static std::uniform_int_distribution<unsigned char> randomColor(60, 255);

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
    
    age::Color fontColor(0x00FFFFFF);
    glm::vec2 scale{0.5f};
    m_font->render(m_batchRenderer, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", glm::vec2{40.0f, 400.0f}, scale, 1.0f, fontColor);
    //scale = glm::vec2(0.9f);
    m_font->render(m_batchRenderer, "abcdefghijklmnopqrstuvwxyz", glm::vec2{40.0f, 350.0f}, scale, 1.0f, fontColor);
    m_font->render(m_batchRenderer, "0123456789", glm::vec2{40.0f, 300.0f}, scale, 1.0f, fontColor);
    m_font->render(m_batchRenderer, "@&'(!)-_*^¨%=+:/;.,?<>", glm::vec2{40.0f, 250.0f}, scale, 1.0f, fontColor);
    //m_font->render(m_batchRenderer, "Hello Word!", glm::vec2{40.0f, 200.0f}, scale, 1.0f, fontColor);
    
    m_batchRenderer.end();
    m_batchRenderer.render();
    
    // Try rendering a Square (LINES primitive)
    age::Square square1 = age::Square(30, 30);
    square1.setPosition(glm::vec2(100, 500));
    square1.setColor(0xFFFF00FF);
    
    age::Square square2 = age::Square(30, 30);
    square2.setPosition(glm::vec2(160, 500));
    square2.setColor(0xFF00FFFF);
    
    m_linesBatchRenderer.begin();
    square1.draw(&m_linesBatchRenderer);
    square2.draw(&m_linesBatchRenderer);
    m_linesBatchRenderer.end();
    // TODO: Why this line width function is not working?
    //glLineWidth(3.5f);
    m_linesBatchRenderer.render();
    
    
    m_basicShader.unbind();
}
