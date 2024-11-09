//
// Created by minha on 10/3/2024.
//

#include "GameEngine.h"
#include "GameEngineDriver.h"

//Instantiate, run and delete game engine
void testGameStates(){
    gameEngine.run();
}

void testStartupPhase(){
    gameEngine.startupPhase();
}
void testMainGameLoop(){
    gameEngine.mainGameLoop();
}

// int main() {
//     testGameStates();
//     return 0;
// }
