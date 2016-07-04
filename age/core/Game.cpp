#include <iostream>
#include <string>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include <GL/glew.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Game.h"
#include "Error.h"
#include "Utils.h"


namespace age {

	Game::Game(std::string gameName) : m_gameName(gameName) {}
	Game::~Game() {}
    
    void Game::addScreen(const std::string& name, Screen* screen) {
        m_screens[name] = screen;
        screen->init();
    }
    
    void Game::setCurrentScreen(const std::string& name) {
        auto it = m_screens.find(name);
        if (it != m_screens.end()) {
            m_currentScreen = it->second;
        }
        else {
            m_currentScreen = nullptr;
        }
        //TODO: handle error case!
    }
    
    const InputManager* Game::getInputManager() const {
        return &m_inputManager;
    }


	void Game::init(Window* window) {

        m_window = window;

        //TODO: use a proper logging lib
		std::cout << "Initializing game " + m_gameName << "\n";

        // Initialize SDL sub systems
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        m_window->init();
        // Do not do any openGl call before the OpenGL Context
        // is created (in the window.init() method)
        Utils::logGlErrors("SDL Init failed");
        
        // TODO: configure the image format accepted (enum)
        int flags = IMG_INIT_JPG | IMG_INIT_PNG;
        int initializedFlags = IMG_Init(flags);
        if((initializedFlags & flags) != flags) {
            std::cerr << "IMG_Init: Failed to init required jpg and png support!\n";
            std::cerr << "IMG_Init: " << IMG_GetError() << std::endl;
        }
        Utils::logGlErrors("SDL_Image Init failed");
        
        SDL_version compile_version;
        const SDL_version *link_version = IMG_Linked_Version();
        SDL_IMAGE_VERSION(&compile_version);
        
        printf("Compiled with SDL_image version: %d.%d.%d\n",
               compile_version.major,
               compile_version.minor,
               compile_version.patch);
        
        printf("Running with SDL_image version: %d.%d.%d\n",
               link_version->major,
               link_version->minor,
               link_version->patch);

#ifndef __APPLE__
		glewExperimental = true;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			fatalError("GLEW init failed!");
		}
#endif
		//Utils::logGlErrors("GLEW Init failed");

        glm::vec4 backgroundColor = m_backgroundColor.toVec4();
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

		// OpenGL Context - Set VSYNC: 0 => FALSE, 1 => TRUE
		SDL_GL_SetSwapInterval(0);

        std::cout << "OpenGL information: \n";
        std::cout << "================== \n";

        std::string unknown("Unknown");
        const GLubyte* glVendor = glGetString(GL_VENDOR) ? glGetString(GL_VENDOR) : (const GLubyte*)unknown.c_str();
        std::cout << " + Vendor: "     <<  glVendor << "\n";
        
        const GLubyte* glRenderer = glGetString(GL_RENDERER) ? glGetString(GL_RENDERER) : (const GLubyte*)unknown.c_str();
		std::cout << " + Renderer: "   << glRenderer << "\n";
        
        const GLubyte* glVersion = glGetString(GL_VERSION) ? glGetString(GL_VERSION) : (const GLubyte*)unknown.c_str();
		std::cout << " + GL Version: " << glVersion << "\n";
        
        const GLubyte* glGLSL = glGetString(GL_SHADING_LANGUAGE_VERSION)
                                    ? glGetString(GL_SHADING_LANGUAGE_VERSION) : (const GLubyte*)unknown.c_str();
		std::cout << " + GLSL: "       << glGLSL << std::endl;

		onInit();
		m_isInitialized = true;
	}
    
	void Game::start() {
		if (m_isInitialized == false) {
			fatalError("Error: Game must be initialized before start could be called!");
		}

		std::cout << "Starting game " << m_gameName << std::endl;
		run();
	}

	void Game::run() {
		std::cout << "Running game " << m_gameName << std::endl;
		m_isRunning = (m_currentScreen != nullptr);
        if (m_currentScreen) {
            m_currentScreen->onEntry();
        }
		
		// FPS / Time variables
		unsigned int previousCumulatedTime = SDL_GetTicks();
		unsigned int startFrameTime;
		unsigned int elapseTime = 0;
		unsigned int deltaTime = 0;
		int delayTime;
		unsigned int cumulatedElapseTime = 0;
		unsigned int frameCounter = 0;
		
		// Setting a FPS Cap higher than 400 seems to not be accurate (due to SDL_Delay)
		const float capFPS = 60.0f;
		const float capElapseTime = 1000.0f / capFPS;
		float actualFPS = 0.0f;
        
		// Game loop
		while (m_isRunning) {
			startFrameTime = SDL_GetTicks();
			frameCounter++;
			checkEvents();

			// Update callback
			m_currentScreen->onUpdate(deltaTime);
            
			// Clear buffers
			glClearDepth(1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render callback
			m_currentScreen->onRender();

			// Swap back and front buffers (display)
            m_window->swapBuffers();

			// Display FPS every 2 sec
			cumulatedElapseTime = SDL_GetTicks() - previousCumulatedTime;
			if (cumulatedElapseTime > 2000) {
				actualFPS = frameCounter / (float)cumulatedElapseTime * 1000.0f;
				frameCounter = 0;
				previousCumulatedTime = SDL_GetTicks();
				printf("FPS: %f\n", actualFPS);
			}

			// FPS and elapse time updates
			elapseTime = SDL_GetTicks() - startFrameTime;

			// FPS Capping
			delayTime = static_cast<int>(capElapseTime - elapseTime);
			// Delay only if it is for more than 2ms
			if (delayTime > 2) {
				SDL_Delay(delayTime);
			}
			deltaTime = SDL_GetTicks() - startFrameTime;
            
            // Check current screen state
            if (m_currentScreen->getState() == ScreenState::GO_NEXT) {
                m_currentScreen->onExit();
                m_currentScreen->setState(ScreenState::INACTIVE);
                setCurrentScreen(m_currentScreen->getNext());
                
                if (m_currentScreen) {
                    m_currentScreen->onEntry();
                    m_currentScreen->setState(ScreenState::ACTIVE);
                }
                else {
                    //TODO: Log in case the screen doesn't exist
                    m_isRunning = false;
                }
            }
		}

        // Screen cleanup
        for (auto scr : m_screens) {
            scr.second->destroy();
        }
        
		// Exit callback
		onExit();
        
        IMG_Quit();
        m_window->destroy();
	}
    
    void Game::checkEvents() {
        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            
            switch(evt.type) {
                case SDL_QUIT:
                    std::cout << "Exit requested" << std::endl;
                    m_isRunning = false;
                    break;
                case SDL_WINDOWEVENT:
                    switch (evt.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            m_window->setSize(evt.window.data1, evt.window.data2);
                            break;
                    }
                    break;
                case SDL_KEYDOWN:
                    m_inputManager.keyPressed(evt.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    m_inputManager.keyReleased(evt.key.keysym.sym);
                    break;
                case SDL_MOUSEMOTION:
                    //std::cout << evt.motion.x << ", " << evt.motion.y << std::endl;
                    break;
                default:
                    break;
            }
        }
        
        m_currentScreen->onInput();
	}
}