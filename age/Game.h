#pragma once

#include <SDL2/SDL.h>

#include "ShaderProgram.h"
#include "InputManager.h"
#include "IPhysicsEngine.h"

struct SDL_Window;
class b2World;
class b2Body;

namespace age {

	class Game
	{
	public:
		Game(std::string gameName);
		virtual ~Game();

		void init(unsigned int windowWidth, unsigned int windowHeight, unsigned int windowFlags = SDL_INIT_EVERYTHING);
		void start();
        void setPhysicsEngine(IPhysicsEngine* engine);

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
        IPhysicsEngine* m_physicsEngine = nullptr;
	};
}