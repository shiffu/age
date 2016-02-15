#include "stdafx.h"

#include "MyTestGame.h"

int main(int argc, char** argv) {
	
	MyTestGame testGame;
	testGame.init(1024, 768);
	testGame.start();

    return 0;
}

