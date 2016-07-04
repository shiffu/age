#pragma once

#include <map>
#include <string>

#include <SDL2/SDL.h>

#include "../rendering/ShaderProgram.h"
#include "../input/InputManager.h"
#include "../physics/IPhysicsEngine.h"
#include "../rendering/Color.h"
#include "Window.h"
#include "Screen.h"

struct SDL_Window;

namespace age {

	class Game
	{
	public:
		Game(std::string gameName);
		virtual ~Game();
        
        const InputManager* getInputManager() const;

		void init(Window* window);
		void setBackgroundColor(Color color) { m_backgroundColor = color;  };
		void start();
        
		// Methods to be implemented in the child class
		virtual void onInit() {}
		virtual void onInput(SDL_Event evt) {}
		virtual void onUpdate(unsigned int deltaTime) {}
		virtual void onRender() {}
		virtual void onExit() {}
        
        // Screens management
        void addScreen(const std::string& name, Screen* screen);
        void setCurrentScreen(const std::string& name);

	private:
		void run();
		void checkEvents();

		std::string m_gameName;
		Window* m_window;
		Color m_backgroundColor = Color(0x000000FF);
		bool m_isRunning = false;
		bool m_isInitialized = false;
        
        std::map<std::string, Screen*> m_screens;
        Screen* m_currentScreen = nullptr;

		InputManager m_inputManager;
	};
}