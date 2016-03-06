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
#include "Sprite.h"
#include "Error.h"
#include "Utils.h"

namespace age {

	Game::Game(std::string gameName) : m_gameName(gameName) {}

	Game::~Game() {}

	void Game::init(unsigned int windowWidth, unsigned int windowHeight, unsigned int windowFlags /*= SDL_INIT_EVERYTHING*/) {
		std::cout << "Initializing game " + m_gameName << std::endl;

        SDL_Init(windowFlags);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        //SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); //Not needed apparently

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // Create the Window
		m_window = SDL_CreateWindow(m_gameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										windowWidth, windowHeight, SDL_WINDOW_OPENGL);
		if (m_window == nullptr) {
			fatalError("Error creating the window!");
		}

		// Create the OpenGL Context
		SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
		if (glContext == nullptr) {
            fatalError(std::string("Error creating the OpenGL Context: ") + SDL_GetError());
		}
		Utils::logGlErrors("SDL Init or GL Context creation failed");

        int flags = IMG_INIT_JPG|IMG_INIT_PNG;
        int initted = IMG_Init(flags);
        if((initted & flags) != flags) {
            std::cerr << "IMG_Init: Failed to init required jpg and png support!\n";
            std::cerr << "IMG_Init: " << IMG_GetError() << std::endl;
        }
        
        SDL_version compile_version;
        const SDL_version *link_version = IMG_Linked_Version();
        SDL_IMAGE_VERSION(&compile_version);
        printf("compiled with SDL_image version: %d.%d.%d\n",
               compile_version.major,
               compile_version.minor,
               compile_version.patch);
        printf("running with SDL_image version: %d.%d.%d\n",
               link_version->major,
               link_version->minor,
               link_version->patch);

		Utils::logGlErrors("SDL_Image Init failed");


#ifndef __APPLE__
		glewExperimental = true;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			fatalError("GLEW init failed!");
		}
#endif

		Utils::logGlErrors("GLEW Init failed");
		glClearColor(0.4f, 0.2f, 0.2f, 1.0f);

		// Set VSYNC: 0 => FALSE, 1 => TRUE
		SDL_GL_SetSwapInterval(0);

		std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        // Temporary code. Without a default VAO,
        // it doesn't work on MAC OS X
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

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
		m_isRunning = true;
		
		// FPS / Time variables
		unsigned int previousFrameTime = SDL_GetTicks();
		unsigned int previousCumulatedTime = previousFrameTime;
		unsigned int currentFrameTime;
		unsigned int elapseTime;
		int delayTime;
		unsigned int cumulatedElapseTime = 0;
		unsigned int frameCounter = 0;
		
		// Setting a FPS Cap higher than 400 seems to not be accurate (due to SDL_Delay)
		const float capFPS = 60.0f;
		const float capElapseTime = 1000.0f / capFPS;
		float actualFPS = 0.0f;

		// Game loop
		while (m_isRunning) {
			frameCounter++;
			processInput();

			// Update callback
			onUpdate();

			// Draw
			glClearDepth(1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render callback
			onRender();

			SDL_GL_SwapWindow(m_window);

			// FPS and elapse time updates
			currentFrameTime = SDL_GetTicks();
			elapseTime = currentFrameTime - previousFrameTime;

			// FPS Capping
			delayTime = capElapseTime - elapseTime;

			// Delay only if it is for more than 2ms
			if (delayTime > 2) {
				SDL_Delay(delayTime);

				// In case of delay, we need to calculate one more time the currentFrameTime
				currentFrameTime = SDL_GetTicks();
			}

			previousFrameTime = currentFrameTime;

			cumulatedElapseTime  = currentFrameTime - previousCumulatedTime;
			// Display FPS every 0.5 sec
			if (cumulatedElapseTime > 500) {
				actualFPS = (float)frameCounter * 1000.0f / (float)cumulatedElapseTime;
				printf("FPS: %f\n", actualFPS);
				frameCounter = 0;
				previousCumulatedTime = currentFrameTime;
			}
		}
        
        IMG_Quit();

		// Exit callback
		onExit();
	}

	void Game::processInput() {
		
		SDL_Event evt;
		while (SDL_PollEvent(&evt)) {

			switch(evt.type) {
			case SDL_QUIT:
				std::cout << "Exit requested" << std::endl;
				m_isRunning = false;
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

		// Input callback
		onInput(evt);
	}
}