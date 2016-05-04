#include "stdafx.h"

#include "MyTestGame.h"

int main(int argc, char** argv) {
	
	MyTestGame testGame;
	testGame.init(1280, 1024);

	testGame.start();

    return 0;
}
