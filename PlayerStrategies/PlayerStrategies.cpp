//
// Created by minha on 11/11/2024.
//

#include "PlayerStrategies.h"
#include "../Orders/Orders.h"


//DO NOT DELETE PLAYER IN THE STRATEGY DECONSTRUCTOR

//----------------Human player----------------


//--------------------------------------------



//----------------Aggressive player----------------

//-------------------------------------------------



//----------------Benevolent player----------------

//------------------------------------------------



//----------------Neutral player------------------

//------------------------------------------------



//----------------Cheater player------------------
CheaterPlayerStrategy::~CheaterPlayerStrategy(){}

void CheaterPlayerStrategy::issueOrder(){
    if(*player->_reinforcementPool>0){
        std::vector<Territory*> owned = toDefend();
        player->_orderList->addOrder(new Deploy("Deploy", owned.at(0), player->_id, player->_reinforcementPool));
    }else{
        player->_orderList->addOrder(new Cheat("Cheat", player->_id));
        *player->_doneTurn=true;
    }
    
}

std::vector<Territory*> CheaterPlayerStrategy::toDefend(){
    std::vector<Territory*> territoriesToDefend;

    // Add all player-owned territories to the vector
    for (int i=0; i<gameMap.graph.size();i++) { // Each time the player concquer a territory, it should be added in _playerTerritory
        if (*gameMap.graph.at(i).owner==*player->_id) {
            territoriesToDefend.push_back(&gameMap.graph.at(i));
        }
    }

    return territoriesToDefend;
}

std::vector<Territory*> CheaterPlayerStrategy::toAttack(){
    std::vector<Territory*> territoriesToAttack;

    // Loop through all territories in the game map
    for (int i=0; i<gameMap.graph.size();i++) {
        // Check if the territory is not owned by the player
        if (*gameMap.graph.at(i).owner!=*player->_id) {
            // Territory is available for attack, push back the pointer to the territory
            territoriesToAttack.push_back(&gameMap.graph.at(i));
        }
    }

    return territoriesToAttack;
}
//------------------------------------------------