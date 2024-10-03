//
// Created by minha on 10/3/2024.
//

#include <iostream>

#include "GameEngine.h"

//Instantiate, run and delete game engine
void testGameStates(){


    GameEngine* gameEngine = new GameEngine();

    gameEngine->run();

    delete gameEngine;
}

int main() {
    // testGameStates();

    State* state = new MapLoaded();
    std::cout << *state;
    return 0;
}