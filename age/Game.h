#pragma once

#include "ShaderProgram.h"

struct SDL_Window;

namespace age {

	class Game
	{
	public:
		Game();
		virtual ~Game();

		void init();
		void start();
		void run();

	private:
		void input();

		SDL_Window*	m_window = nullptr;
		bool m_isRunning = false;

		ShaderProgram m_basicShaderProgram;
	};
}