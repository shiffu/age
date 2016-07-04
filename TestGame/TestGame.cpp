#include "stdafx.h"

#include "MyTestGame.h"
#include "LevelScreen.h"
#include "MainMenu.h"

int main(int argc, char** argv) {
    age::Window myWindow("My Awesome Test Game", 1024, 960, age::WindowFlag::MAXIMIZE);
    
    MyTestGame testGame;
    testGame.init(&myWindow);
    
    MainMenu mainMenu;
    mainMenu.setGame(&testGame);
    testGame.addScreen("MainMenu", &mainMenu);
    
    LevelScreen level1(1);
    level1.setGame(&testGame);
    testGame.addScreen("Level1", &level1);
    
    testGame.setCurrentScreen("MainMenu");
    
    testGame.start();
    
    return 0;
}
