#pragma once

#include <SDL2/SDL.h>

#include "ShaderProgram.h"
#include "InputManager.h"
#include "IPhysicsEngine.h"
#include "Color.h"

struct SDL_Window;

namespace age {

	class Game
	{
	public:
		Game(std::string gameName);
		virtual ~Game();

		void init(unsigned int windowWidth, unsigned int windowHeight, unsigned int windowFlags = SDL_INIT_EVERYTHING);
		void setBackgroundColor(Color color) { m_backgroundColor = color;  };
		void start();

		// Methods to be implemented in the child class
		virtual void onInit() {}
		virtual void onInput(SDL_Event evt) {}
		virtual void onUpdate(unsigned int deltaTime) {}
		virtual void onRender() {}
		virtual void onExit() {}

	private:
		void run();
		void processInput();

		std::string m_gameName;
		SDL_Window*	m_window = nullptr;
		// Default: Black background
		Color m_backgroundColor = Color(0x000000FF);
		bool m_isRunning = false;
		bool m_isInitialized = false;

	protected:
		InputManager m_inputManager;
	};
}