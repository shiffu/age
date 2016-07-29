#pragma once

#include <core/Screen.h>
#include <rendering/ParticleEngine2D.h>
#include <rendering/ParticleBatch2D.h>
#include <rendering/Basic2DShader.h>
#include <rendering/BatchRenderer2D.h>
#include <rendering/Camera2D.h>
#include <rendering/SpriteFont.h>
#include <gui/GUIManager.h>
#include <audio/Sound.h>

class MainMenu : public age::Screen {
    
    enum class MenuItem {
        NONE,
        START,
        QUIT
    };
    
public:
    MainMenu() {};
    ~MainMenu() {};
    
    virtual std::string getNext() const;
    
    virtual void onInit();
    virtual void onExit();
    virtual void onDestroy();
    
    virtual void onEntry();
    virtual void onInput();
    virtual void onUpdate(float deltaTime);
    virtual void onRender();
    
private:
    age::Basic2DShader m_basicShader;
    age::BatchRenderer2D m_batchRenderer;
    age::BatchRenderer2D m_linesBatchRenderer;
    
    age::Sound* m_sound;
    
    age::GUIManager m_guiManager;
    age::Button* m_startButton = nullptr;
    age::Button* m_quitButton = nullptr;
    age::Label* m_quitLabel = nullptr;
    age::Label* m_playLabel = nullptr;
    
    age::Camera2D m_camera;

    age::ParticleEngine2D* m_particuleEngine = nullptr;
    age::ParticleBatch2D* m_particuleBatch = nullptr;
    age::Texture* m_particuleTexture = nullptr;
    
    age::SpriteFont* m_font;
    MenuItem m_currentMenuItem = MenuItem::NONE;
};