#include "stdafx.h"

#include "MyTestGame.h"
#include "LevelScreen.h"
#include "MainMenu.h"

int main(int argc, char** argv) {
    age::Window myWindow("My Awesome Test Game", 800, 600);
    
    MyTestGame testGame;
    testGame.init(&myWindow);
    
    MainMenu mainMenu;
    testGame.addScreen("MainMenu", &mainMenu);
    
    LevelScreen level1(1);
    testGame.addScreen("Level1", &level1);
    
    testGame.setCurrentScreen("MainMenu");
    
    testGame.start();
    
    return 0;
}
