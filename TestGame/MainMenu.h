#pragma once

#include <core/Screen.h>
#include <rendering/ParticleEngine2D.h>
#include <rendering/ParticleBatch2D.h>
#include <rendering/Basic2DShader.h>
#include <rendering/BatchRenderer2D.h>
#include <rendering/Camera2D.h>

class MainMenu : public age::Screen {
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
    age::Camera2D m_camera;

    age::ParticleEngine2D* m_particuleEngine = nullptr;
    age::ParticleBatch2D* m_particuleBatch = nullptr;
    age::Texture* m_particuleTexture = nullptr;
};