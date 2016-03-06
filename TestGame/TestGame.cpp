#ifdef _WIN32
#include "stdafx.h"
#endif

#include "MyTestGame.h"

int main(int argc, char** argv) {
	
	MyTestGame testGame;
	testGame.init(800, 600);

	testGame.start();

    return 0;
}
