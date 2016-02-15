#include "Error.h"

#include <cstdlib>

#include <iostream>
#include <SDL/SDL.h>

namespace age {

	void fatalError(const std::string& errMsg) {
		std::cerr << errMsg << std::endl;
		std::cout << "Press any key to quit!" << std::endl;
		std::cin.get();
		SDL_Quit();
		exit(1);
	}
}