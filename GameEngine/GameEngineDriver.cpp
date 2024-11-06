//
// Created by minha on 10/3/2024.
//

#include "GameEngine.h"
#include "GameEngineDriver.h"

//Instantiate, run and delete game engine
void testGameStates(char **argv){

    GameEngine* gameEngine = new GameEngine(argv);

    gameEngine->run();

    delete gameEngine;
}

// int main() {
//     testGameStates();
//     return 0;
// }
