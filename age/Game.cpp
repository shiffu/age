#include <iostream>
#include <string>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Game.h"
#include "Sprite.h"
#include "Error.h"

namespace age {

	Game::Game() {}

	Game::~Game() {}

	void Game::init() {
		std::cout << "Init game" << std::endl;

		SDL_Init(SDL_INIT_EVERYTHING);

		// Create the Window
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		m_window = SDL_CreateWindow("Test Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
		if (m_window == nullptr) {
			fatalError("Error creating the window!");
		}

		// Create the OpenGL Context
		SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
		if (glContext == nullptr) {
			fatalError("Error creating the OpenGL Context!");
		}

		GLenum err = glewInit();
		if (err != GLEW_OK) {
			fatalError("GLEW init failed!");
		}

		glClearColor(0, 0, 1.0f, 1.0f);

		// Set VSYNC: 0 => FALSE, 1 => TRUE
		SDL_GL_SetSwapInterval(0);

		std::cout << glGetString(GL_VENDOR) << std::endl;
		std::cout << glGetString(GL_RENDERER) << std::endl;
		std::cout << glGetString(GL_VERSION) << std::endl;
		std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		// Init Shader Program
		//TODO: Do not hardcode the path to resources (resourceManager)
		m_basicShaderProgram.compileShaders("../age/shaders/basic");
		m_basicShaderProgram.linkProgram();
		m_basicShaderProgram.bindAttribute("position");
		m_basicShaderProgram.bindAttribute("color");
	}

	void Game::start() {
		std::cout << "Start game" << std::endl;
		init();
		run();
	}

	void Game::run() {
		std::cout << "Run game" << std::endl;
		m_isRunning = true;
		Sprite sprite;
		sprite.init(0, 0, 0.5f, 0.5f);
		float time = 0.0f;
		
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
			input();

			// Draw
			glClearDepth(1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// TEST CODE TO BE REMOVED!!
				m_basicShaderProgram.bind();
				time += 0.03f;

				m_basicShaderProgram.setUniform("time", time);

				sprite.draw();
				m_basicShaderProgram.unbind();

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
	}

	void Game::input() {
		
		SDL_Event evt;
		while (SDL_PollEvent(&evt)) {

			switch(evt.type) {
			case SDL_QUIT:
				std::cout << "QUIT pressed" << std::endl;
				m_isRunning = false;
				break;
			case SDL_MOUSEMOTION:
				//std::cout << evt.motion.x << ", " << evt.motion.y << std::endl;
				break;
			default:
				break;
			}
		}
	}
}