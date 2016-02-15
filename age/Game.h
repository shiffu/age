#pragma once

#include "ShaderProgram.h"
#include "InputManager.h"

struct SDL_Window;

namespace age {

	class Game
	{
	public:
		Game(std::string gameName);
		virtual ~Game();

		void init(unsigned int windowWidth, unsigned int windowHeight, unsigned int windowFlags = SDL_INIT_EVERYTHING);
		void start();

		// Methods to be implemented in the child class
		virtual void onInit() {}
		virtual void onInput(SDL_Event evt) {}
		virtual void onUpdate() {}
		virtual void onRender() {}
		virtual void onExit() {}

	private:
		void run();
		void processInput();

		std::string m_gameName;
		SDL_Window*	m_window = nullptr;
		bool m_isRunning = false;
		bool m_isInitialized = false;

	protected:
		InputManager m_inputManager;
	};
}