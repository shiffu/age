#include "stdafx.h"

#include "MyTestGame.h"

int main(int argc, char** argv) {
    age::Window myWindow("My Awesome Test Game", 1024, 960, age::WindowFlag::FULLSCREEN);
    
    MyTestGame testGame;
    testGame.init(&myWindow);
    
    testGame.start();
    
    return 0;
}
