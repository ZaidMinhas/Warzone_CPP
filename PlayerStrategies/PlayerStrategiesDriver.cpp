//
// Created by minha on 11/11/2024.
//

#include "PlayerStrategiesDriver.h"
#include "PlayerStrategies.h"
#include "../Player/Player.h"
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"


void testPlayerStrategies(){
    //Setting up the game

    gameMap.loadMap("Map/Asia.map");
    playerList.clear();
    gameEngine=GameEngine();

    int* playerId_1 = new int(0);
    int* playerId_2 = new int(1);
    int* playerId_3 = new int(2);
    int* playerId_4 = new int(3);
    int* playerId_5 = new int(4);

    Player* player1 = new Player("Player 1 Aggressive", playerId_1);
    
    Player* player2 = new Player("Player 2 Benevolent", playerId_2);
    
    Player* player3 = new Player("Player 3 Neutral", playerId_3);

    Player* player4 = new Player("Player 4 Cheater", playerId_4);

    Player* player5 = new Player("Player 5 Human", playerId_5);

    playerList.push_back(player1);
    playerList.push_back(player2);
    playerList.push_back(player3);
    playerList.push_back(player4);
    playerList.push_back(player5);

    //Assign players with a strategy

    player1->setPlayerStrategy("Aggressive");
    player2->setPlayerStrategy("Benevolent");
    player3->setPlayerStrategy("Neutral");
    player4->setPlayerStrategy("Cheater");

    gameEngine.gamestart();
    gameEngine.transition(new AssignReinforcement());
    gameEngine.mainGameLoop();
    

    

    //Change strategies mid game

    //Have human player make decisions by user
}