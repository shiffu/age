#pragma once

#include <SDL2/SDL.h>

#include "../rendering/ShaderProgram.h"
#include "../input/InputManager.h"
#include "../physics/IPhysicsEngine.h"
#include "../rendering/Color.h"
#include "Window.h"

struct SDL_Window;

namespace age {

	class Game
	{
	public:
		Game(std::string gameName);
		virtual ~Game();

		void init(Window* window);
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
		void checkEvents();

		std::string m_gameName;
		Window* m_window;
		Color m_backgroundColor = Color(0x000000FF);
		bool m_isRunning = false;
		bool m_isInitialized = false;

	protected:
		InputManager m_inputManager;
	};
}