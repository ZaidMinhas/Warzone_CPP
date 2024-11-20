

#include "PlayerStrategies.h"
#include "../Orders/Orders.h"
#include <algorithm>
#include <iostream>
#include <sstream> //spliting the command line
#include <utility>
#include "../CommandProcessor/CommandProcessor.h"


//DO NOT DELETE PLAYER IN THE STRATEGY DECONSTRUCTOR

//----------------Human player----------------
HumanPlayerStrategy::~HumanPlayerStrategy(){}

void HumanPlayerStrategy::issueOrder(){

    //get the arguments from command arg[0] -> should mention to the player how to enter the command
    //command :  deploy 50 canada | arg[0]->deploy ; arg[1]->numbr of units ; arg[2]->terriroty on which the player deploys his armies
    //switch case of if deploy, if advance , if bomb , if airlift , if blockade , if negociate

    // Do not use command processor for orders
    // std::string command=commandProcessor->getCommand();

    cout << "Issue an order: ";
    string command;
    std::getline(cin, command);

    int* playerId = player->_id;
    // the split words
    std::vector<std::string> args;

    // string stream to split the command by spaces
    std::istringstream iss(command);
    std::string word;
    while (iss >> word) {
        args.push_back(word); //trims words
    }

    //if deploy : arg[0] = deploy and reinforce>0 (aka player has troops)
    if (args[0] == "deploy" && *player->_reinforcementPool>0 && *player->_reinforcementPool>=std::stoi(args[1])) { // player should have units to deploy - otherwise cannot deploy
        //command deploy 15 canada
        //Deploy(string orderName,Territory* toDeploy,int* playerIndex,int* nUnits); - signature

        std::string orderName = args[0];  // e.g., "deploy"

        //COUNTRIES WITH MULTIPLE WORDS
        std::string toDeploy = args[2];
        if (args.size() == 4) {
            toDeploy += " " + args[3];
        }

        /*
        for (int i = 3; i < args.size(); i++) {
          toDeploy += " " + args[i];
        }
         */
        Territory* toDeployIn = player->findTerritoryByName(toDeploy);
        //MAKE SURE THAT THIS IS A POINTER AND NOT A VARIABLS
        int* nUnits = new int(std::stoi(args[1]));  // to convert the number of units to int
        //Deploy* deployOrder = new Deploy(orderName, toDeploy, playerIndex, new int(nUnits));
        player->_orderList->addOrder(new Deploy(orderName, toDeployIn, playerId, nUnits));

        *player->_reinforcementPool=*player->_reinforcementPool-std::stoi(args[1]);

    } else if (args[0] == "advance" && *player->_reinforcementPool==0) { //player should deploy all the units before advancing // more conditions?
        //command : advance 12 iraq , iran
        // Advance::Advance(string orderName,int* playerIndex,Territory* advanceFrom,Territory* advanceTo,int* nUnits) - signature
        std::string orderName = args[0];  
        int* nUnits = new int(std::stoi(args[1]));
        int counter = 2;
        std::string owned = args[2];
        for(counter=3;counter<args.size();counter++){
            if(args[counter] == ","){
                break;
            }
            else{
                owned += " "+args[counter];
            }
        }
        std::string target = args[++counter];
        for(++counter;counter<args.size();counter++){
            target += " "+args[counter];
        }
        cout<<"Advancing from: "<<owned<<endl;
        cout<<"Advancing to: "<<target<<endl;

        Territory* _owned = player->findTerritoryByName(owned);
        Territory* _target = player->findTerritoryByName(target);

        cout<<*(_target->name)<<endl;

        //territories should be the adjacent territories
        player->_orderList->addOrder(new Advance(orderName, playerId, _owned, _target, nUnits));

    } else if (args[0] == "blockade" && *player->_reinforcementPool==0) { 
        //command : blockade indonesia
        //Blockade::Blockade(string orderName,int* playerIndex,Territory* toBlock) - Signature
        if (player->hasCardType("blockade")) {
            std::string orderName = args[0]; 
            std::string target = args[1];
            if (args.size() == 3) {
                target += " " + args[2];
            }
            Territory* _target = player->findTerritoryByName(target);

            cout<<*(_target->name)<<"Is preparing a blockade!!!"<<endl;

            player->_orderList->addOrder(new Blockade(orderName, playerId, _target));
        } else {
            std::cout << "You do not have a blockade card.\n";
        }

    } else if (args[0] == "airlift" && *player->_reinforcementPool==0) {
        //command : airlift 18 indonesia philippines
        //Airlift::Airlift(string orderName,int* playerIndex,Territory* airliftFrom,Territory* airliftTo,int* nUnits) -- Signature
        if (player->hasCardType("airlift")) {
            std::string orderName = args[0];  
            int* nUnits = new int(std::stoi(args[1]));
            std::string owned = args[2];
            std::string target = args[3];

            Territory* _owned = player->findTerritoryByName(owned);
            Territory* _target = player->findTerritoryByName(target);
            int* playerIndex = playerId;

            player->_orderList->addOrder(new Airlift(orderName, playerIndex, _owned, _target, nUnits));
        } else {
            std::cout << "You do not have an Airlift card.\n";
        }

    } else if (args[0] == "negotiate" && *player->_reinforcementPool==0) {
        //command : negociate
        // Negotiate::Negotiate(string orderName,int* playerIndex)
        if (player->hasCardType("diplomacy")) {
            std::string orderName = args[0];
            int* playerIndex = playerId;
            int toNegotiate = std::stoi(args[1]);


            player->_orderList->addOrder(new Negotiate(orderName, playerIndex, toNegotiate));
        } else {
            std::cout << "You do not have a Negociate card.\n";
        }

    } else if (args[0] == "bomb" && *player->_reinforcementPool==0) {
        //command : bomb philippines
        // Bomb::Bomb(string orderName,int* playerIndex,Territory* toBomb) -- Signature
        if (player->hasCardType("bomb")) { 
            std::string orderName = args[0];  
            std::string target = args[1];
            if (args.size() == 3) {
                target += " " + args[2];
            }
            Territory* _target = player->findTerritoryByName(target);
            int* playerIndex = playerId;

            cout<<"Target to be bombed "<<*(_target->name)<<endl;

            Bomb* bombOrder = new Bomb(orderName, playerIndex, _target);
            player->_orderList->addOrder(bombOrder);
        } else {
            std::cout << "You do not have a Bomb card.\n";
        }

    // Player has done turn
    }else if(args[0]=="done"){
            *player->_doneTurn=true;
        } 
    
    else {
        std::cout << "Command: " << args[0] << " failed to process." << std::endl;
    }

}

std::vector<Territory*> HumanPlayerStrategy::toDefend(){
    std::vector<Territory*> territoriesToDefend;

    // Add all player-owned territories to the vector
    for (int i=0; i<gameMap.graph.size();i++) { // Each time the player concquer a territory, it should be added in _playerTerritory
        if (*gameMap.graph.at(i).owner==*player->_id) {
            territoriesToDefend.push_back(&gameMap.graph.at(i));
        }
    }

    return territoriesToDefend;
}

std::vector<Territory*> HumanPlayerStrategy::toAttack(){
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

//--------------------------------------------



//----------------Aggressive player----------------

AggressivePlayerStrategy::~AggressivePlayerStrategy(){}

void AggressivePlayerStrategy::issueOrder(){
    std::vector<Territory*> owned = toDefend();
    std::vector<Territory*> targets = toAttack();
    bool turnOver=false;
    bool advanced=false;
    if (*player->_reinforcementPool>0){
        //Deploy
        int* nUnits = new int(*player->_reinforcementPool);
        player->_orderList->addOrder(new Deploy("Deploy", owned.at(0), player->_id, nUnits));
        *player->_reinforcementPool=0;
        turnOver=true;
    }else{

        //Using the bomb card if available
        for(int i=0;i<player->getHand()->getCards().size();i++){
            if(player->getHand()->getCards().at(i).getType()=="Bomb"){
                for(int j=0;j<owned.at(0)->connections.size();j++){
                    if(*owned.at(0)->connections.at(j)->owner!=*player->_id && *owned.at(0)->connections.at(j)->army>0){
                        player->_orderList->addOrder(new Bomb("Bomb", player->_id, owned.at(0)->connections.at(j)));
                        turnOver=true;
                        break;
                    }
                }
            }
        }

        //Advance
        if(turnOver==false){
            for(int j=0;j<owned.at(0)->connections.size();j++){
                if(*owned.at(0)->connections.at(j)->owner!=*player->_id && *owned.at(0)->connections.at(j)->army<=*owned.at(0)->army){
                    int* nUnits = new int(*owned.at(0)->army);
                    player->_orderList->addOrder(new Advance("Advance", player->_id, owned.at(0), owned.at(0)->connections.at(j), nUnits));
                    turnOver=true;
                    advanced=true;
                    *player->_doneTurn=true;
                    break;
                }
            }
            if(advanced==false){
                *player->_doneTurn=true;
            }
        }
    }
}


std::vector<Territory*> AggressivePlayerStrategy::toDefend(){
    std::vector<Territory*> territoriesToDefend;

    // Add all player-owned territories to the vector
    for (int i=0; i<gameMap.graph.size();i++) { // Each time the player concquer a territory, it should be added in _playerTerritory
        if (*gameMap.graph.at(i).owner==*player->_id) {
            for(int j=0;j<gameMap.graph.at(i).connections.size();j++){
                if(*gameMap.graph.at(i).connections.at(j)->owner!=*player->_id){
                    territoriesToDefend.push_back(&gameMap.graph.at(i));
                    break;
                }
            }
            
        }
    }

    std::sort(territoriesToDefend.begin(), territoriesToDefend.end(),
              [](Territory* a, Territory* b) { return *a->army > *b->army; });

    return territoriesToDefend;
}

std::vector<Territory*> AggressivePlayerStrategy::toAttack(){
    std::vector<Territory*> territoriesToAttack;

    // Loop through all territories in the game map
    for (int i=0; i<gameMap.graph.size();i++) {
        // Check if the territory is not owned by the player
        if (*gameMap.graph.at(i).owner!=*player->_id) {
            // Territory is available for attack, push back the pointer to the territory
            for(int j=0;j<gameMap.graph.at(i).connections.size();j++){
                if(*gameMap.graph.at(i).connections.at(j)->owner==*player->_id){
                    territoriesToAttack.push_back(&gameMap.graph.at(i));
                    break;
                }
            }
        }
    }

    

    return territoriesToAttack;
}

//-------------------------------------------------



//----------------Benevolent player----------------

BenevolentPlayerStrategy::~BenevolentPlayerStrategy(){}

void BenevolentPlayerStrategy::issueOrder(){
    // Focus on reinforcing the weakest territories --> REQ 1
    std::vector<Territory*> defendList = toDefend();
    if(defendList.empty()){
        std::cout << "There's not territories to defend" << std::endl; // any territories to defend?
        return;
    }

    if(*player->_reinforcementPool>0){ // if there are units to deploy ...
        // armies deployment to the weakest territories for defence
        Territory* weakestTerritory = defendList.front();
        int* nUnits = new int(*player->_reinforcementPool);
        player->_orderList->addOrder(new Deploy("Deploy", weakestTerritory, player->_id, nUnits));
        *player->_reinforcementPool = 0; // empty reinforcement pool
        std::cout << "All armies deloyed to protect " << *(weakestTerritory->name) << "." << std::endl;
    } else {
        // no reiforcement ? --> advance
        if(defendList.size()<1){
            Territory* original_territory = defendList.at(1); // next weakest territory on the defend list
            Territory* target_territory = defendList.front(); // weakest territory NOW
            int *nUnits = new int(*original_territory->army/2 ); // advance half the armies
            player->_orderList->addOrder(new Advance("Advance", player->_id, original_territory, target_territory, nUnits));
            std::cout << "Armies advanced from " << *(original_territory->name) << " to " << *(target_territory->name) << "." << std::endl;
            *player->_doneTurn=true;
        } else {
            //std::cout << "You cannot advance to protect territories." << std::endl;
            *player->_doneTurn=true;
        }
    }

}

std::vector<Territory*> BenevolentPlayerStrategy::toDefend() {
    std::vector<Territory*> territoriesToDefend;

    // add all territories owned by the player 
    for (auto& territory : gameMap.graph) {
        if (*territory.owner == *player->_id) {
            territoriesToDefend.push_back(&territory);
        }
    }

    // sort the territories by the number of armies in ascending order -> to determine afterwards the weakest territories 
    std::sort(territoriesToDefend.begin(), territoriesToDefend.end(),
              [](Territory* a, Territory* b) { return a->army < b->army; });

    return territoriesToDefend;
}

std::vector<Territory*> BenevolentPlayerStrategy::toAttack() { //based on the requirements, benevolent player NEVER attacks
    return {};
}

//------------------------------------------------



//----------------Neutral player------------------
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

void NeutralPlayerStrategy::issueOrder() { //based on the requirements, neutral player NEVER issues orders
    std::cout << "Neutral player does not issue orders!" << std::endl;
    *player->_doneTurn=true;
}

std::vector<Territory*> NeutralPlayerStrategy::toDefend() { //based on the requirements, neutral player doesn't defend 
    return {};
}

std::vector<Territory*> NeutralPlayerStrategy::toAttack() { //based on the requirements, neutral player doesn't attack 
    return {};
}

void NeutralPlayerStrategy::handleAttack() { // If attacked, neutral player switches to aggressive player
    std::cout << "Neutral player has been attacked! Switching to Aggressive ..." << std::endl;
    player->setPlayerStrategy("Aggressive");
}
//------------------------------------------------



//----------------Cheater player------------------
CheaterPlayerStrategy::~CheaterPlayerStrategy(){}

void CheaterPlayerStrategy::issueOrder(){
    if(*player->_reinforcementPool>0){
        std::vector<Territory*> owned = toDefend();
        int* nUnits = new int(*player->_reinforcementPool);
        player->_orderList->addOrder(new Deploy("Deploy", owned.at(0), player->_id, nUnits));
        *player->_reinforcementPool=0;
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