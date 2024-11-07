
#include "Player.h"
#include <algorithm>
#include <iostream>
#include <sstream> //spliting the command line
#include <utility>
#include "..\Orders\Orders.h"


//Player::Player(){}; 
Player::Player() : _orderList(new OrdersList()) {} // Added - K - A2

/*Player::Player(const string &name, const vector<string*> &territory, const vector<string*> &hand, const vector<string*> &order)
{
    this->_name = name;
    this->_territories = territory;
    this->_handCard = hand;
    this->_orderList = order;
}*/

Player::Player(const string &name, int* id){
    this->_name = name;
    this->_id=new int(*id);
}

//copy constructor
Player::Player(const Player& other)
{
    this->_name = other._name;
    this->_territories = other._territories;
    this->_handCard = other._handCard;
    this->_playerterritories = other._playerterritories;
    _orderList = new OrdersList(*other._orderList);
}

//destructor
Player::~Player()
{
    this->_name.clear();
    this->_territories.clear();
    delete _handCard;
    delete _orderList; // changed - K - A2
}

// Assignment operator
Player& Player::operator=(const Player& other) {
    if (this == &other) return *this; // Self-assignment check

    delete _id;
    delete _handCard;
    delete _orderList;

    _name = other._name;
    _territories = other._territories;
    _handCard = other._handCard;
    _playerterritories = other._playerterritories;

    _orderList = new OrdersList(*other._orderList); // Deep copy

    return *this;
}

// Issue an order
/*void Player::issueOrder(string order) {
    _orderList.push_back(new string(order)); 
} -- old */ 

/*void Player::issueOrder(const string& orderName) { // changed - K - A2
    Order* newOrder = new Order(orderName);  // Create a new order
    _orderList->addOrder(newOrder);          // Add the new order to the actual OrdersList
}*/

// Print the list of orders

/*void Player::printOrder() const {
    for (const string* order : _orderList) {
        cout << *order << endl;
    }
} old*/

/*void Player::printOrder() const {
    cout << *_orderList; // Overloaded << operator will handle OrdersList printing -> changing the method instead
}*/

void Player::printOrder() const { // changed - K - A2
    if (_orderList->getSize() == 0) {
        std::cout << "Order list is empty." << std::endl;
        return;
    }

    std::cout << "Here is your list of current orders, Commander:" << std::endl;
    Order* currentOrder = _orderList->getHead()->getNext(); // Start from the first actual order
    int index = 1;

    while (currentOrder != _orderList->getTail()) {
        std::cout << "(" << index++ << ") " << currentOrder->getOrderName() << std::endl;
        currentOrder = currentOrder->getNext();
    }
}

// Return a vector of orders
/*vector<string*> Player::getOrderList() {
    return _orderList;
}*/

// Return the OrdersList
OrdersList* Player::getOrderList() { // changed - K - A2
    return _orderList;
}

// Print the hand cards
void Player::printHand() const {
    std::cout << _name << "'s hand cards:\n";
    std::cout << *_handCard;
}

void Player::setHand(Hand* hand) {
    if (_handCard==nullptr) {
        delete _handCard;  // Clean up existing hand 
    }
    _handCard = hand;      // Assign new hand
}

Hand* Player::getHand(){
    return this->_handCard;
}

int Player::getID(){
    return *this->_id;
}


//New method - K - A2
// --------------------------------------------------
//         Find territory object by name
// --------------------------------------------------
Territory* Player::findTerritoryByName(const std::string& territoryName, const std::vector<Territory*>& allTerritoriesInMap) {  //allTerritoriesInMap is a vector that contains all the territories
    for (auto* territory : allTerritoriesInMap) {
        if (territory && territory->name && *(territory->name) == territoryName) {
            return territory;  // Territory found
        }
    }
    return nullptr;  // Territory not found
} // when a player enters a territory name, this function should be called to check if the territory exists



//Defend changed - K - A2
// --------------------------------------------------
//                 Issue Order
// --------------------------------------------------

void Player::issueOrder(const std::string& command, int* playerId, const std::vector<Territory*>& allTerritoriesInMap){
    //get the arguments from command arg[0] -> should mention to the player how to enter the command
    //command :  deploy 50 canada | arg[0]->deploy ; arg[1]->numbr of units ; arg[2]->terriroty on which the player deploys his armies
    //switch case of if deploy, if advance , if bomb , if airlift , if blockade , if negociate

    // the split words
    std::vector<std::string> args;

    // string stream to split the command by spaces
    std::istringstream iss(command);
    std::string word;
    while (iss >> word) {
        args.push_back(word); //trims words
    }

    // Print the player ID
    ///std::cout << "Player ID: " << *playerId << std::endl;

    // the split command words -- test only
    /*std::cout << "Split command words:\n";
    for (size_t i = 0; i < args.size(); ++i) {
        std::cout << "arg[" << i << "]: " << args[i] << '\n';
    }*/

    //if deploy : arg[0] = deploy and reinforce>0 (aka player has troops)
    if (args[0] == "deploy" && *(_reinforcementPool)>0) { // player should have units to deploy - otherwise cannot deploy
        //std::cout << "Deploy command recognized\n";
        // add deploy order // deploy 15 canada
        //Deploy(string orderName,Territory* toDeploy,int* playerIndex,int* nUnits); - signature

        std::string orderName = args[0];  // e.g., "deploy"
        std::string toDeploy = args[2];   // e.g., the territory name
        Territory* toDeployIn = findTerritoryByName(toDeploy, allTerritoriesInMap);
        int nUnits = std::stoi(args[1]);  // to convert the number of units to int
        int* playerIndex = playerId;      
        //Deploy* deployOrder = new Deploy(orderName, toDeploy, playerIndex, new int(nUnits));
        Deploy* deployOrder = new Deploy(orderName, toDeployIn, playerId, &nUnits); 
        _orderList->addOrder(deployOrder);

    } else if (args[0] == "advance" && _reinforcementPool==0) { //player should deploy all the units before advancing
        //std::cout << "Advance command recognized\n";
        // add advance order // command : advance 12 iraq syria

        //Advance* advanceOrder = new Advance("advance", playerId, args[2], args[3], std::stoi(args[1])); //territories should be the adjacent territories
        //_orderList->addOrder(advanceOrder);

    } else if (args[0] == "blockade") {
        std::cout << "Blockade command recognized\n";
        // Blockade* blockadeOrder = new Blockade("blockade", targetTerritory, playerId);
        // _orderList->addOrder(blockadeOrder);

    } else if (args[0] == "airlift") {
        std::cout << "Airlift command recognized\n";
        // Airlift* airliftOrder = new Airlift("airlift", sourceTerritory, targetTerritory, playerId, units);
        // _orderList->addOrder(airliftOrder);

    } else if (args[0] == "negotiate") {
        std::cout << "Negotiate command recognized\n";
        // Negotiate* negotiateOrder = new Negotiate("negotiate", otherPlayerId, playerId);
        // _orderList->addOrder(negotiateOrder);

    } else if (args[0] == "bomb") {
        std::cout << "Bomb command recognized\n";
        // Bomb* bombOrder = new Bomb("bomb", targetTerritory, playerId);
        // _orderList->addOrder(bombOrder);

    } else {
        std::cout << "Command: " << args[0] << " failed to process." << std::endl;
    }
}


//Defend changed - K - A2
// --------------------------------------------------
//              Territories to attack
// --------------------------------------------------
std::vector<Territory*> Player::toAttack() const {
    std::vector<Territory*> territoriesToAttack;

    // Loop through all territories in the game map
    for (const Territory& territory : gameMap.graph) {
        // Check if the territory is not owned by the player
        if (std::find(_playerterritories.begin(), _playerterritories.end(), &territory) == _playerterritories.end()) {
            // Territory is available for attack, push back the pointer to the territory
            territoriesToAttack.push_back(const_cast<Territory*>(&territory));
        }
    }

    return territoriesToAttack;
}


//Defend changed - K - A2
// --------------------------------------------------
//              Territories to defend
// --------------------------------------------------
std::vector<Territory*> Player::toDefend() const {
    std::vector<Territory*> territoriesToDefend;

    // Add all player-owned territories to the vector
    for (const auto& territory : _playerterritories) { // Each time the player concquer a territory, it should be added in _playerTerritory
        territoriesToDefend.push_back(territory);
    }

    return territoriesToDefend;
}


// --------------------------------------------------
//           Territories to add from map
// --------------------------------------------------
void Player::addTerritory(Territory* territory) {
    territory->owner=this->_id;
    _playerterritories.push_back(territory);
}

std::vector<Territory*> Player::getTerritories() const { // new - A2 - K
    return _playerterritories;
}

// Operator to display player information (optional)
ostream& operator<<(ostream &out, const Player &player) {
    out << "Player Name: " << player.getName();
    return out;
}

// Implementing the getName() method with the const qualifier
std::string Player::getName() const {
    return _name;
}

std::vector<Player*> playerList;