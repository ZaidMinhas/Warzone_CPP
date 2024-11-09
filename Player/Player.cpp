
#include "Player.h"
#include <algorithm>
#include <iostream>
#include <sstream> //spliting the command line
#include <utility>
#include "../Orders/Orders.h"


//Player::Player(){}; 
Player::Player() : _orderList(new OrdersList()) {} // Added - K - A2

Player::Player(const string &name, int* id){
    this->_name = name;
    this->_id=new int(*id);
    this->_orderList=new OrdersList();
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

// check if the player has more orders to issue
bool Player::hasMoreOrders() const {
    return _orderList->getSize() > 0;  // Returns true if there are orders in the list
}

// Return the OrdersList
OrdersList* Player::getOrdersList() { // changed - K - A2
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


// ------------------------------------------------
//            Find Territory by name
// ------------------------------------------------
Territory* Player::findTerritoryByName(const std::string& territoryName) {  //allTerritoriesInMap is a vector that contains all the territories
    for (Territory &territory : gameMap.graph) {
        if (*(territory.name) == territoryName) {
            return &territory;  // Territory found
        }
    }
    return nullptr;  // Territory not found
} // when a player enters a territory name, this function should be called to check if the territory exists


// -------------------------------------------------
//   If player choice of card exists in their hand
// -------------------------------------------------
bool Player::hasCardType(const std::string& cardType) {
    Hand* hand = getHand();
    if (!hand) {
        std::cout << "Player has no hand." << std::endl;
        return false;
    }

    const std::vector<Cards>& cardsInHand = hand->getCards();
    for (const auto& card : cardsInHand) {
        if (card.getType() == cardType) {
            return true;
        }
    }
    return false;
}


// --------------------------------------------------
//                 Issue Order
// --------------------------------------------------

void Player::issueOrder(const std::string& command, int* playerId){
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

    //if deploy : arg[0] = deploy and reinforce>0 (aka player has troops)
    if (args[0] == "deploy" && *_reinforcementPool>0 && *_reinforcementPool>=std::stoi(args[1])) { // player should have units to deploy - otherwise cannot deploy
        //command deploy 15 canada
        //Deploy(string orderName,Territory* toDeploy,int* playerIndex,int* nUnits); - signature

        std::string orderName = args[0];  // e.g., "deploy"
        std::string toDeploy = args[2];   // e.g., the territory name
        Territory* toDeployIn = findTerritoryByName(toDeploy);
        int nUnits = std::stoi(args[1]);  // to convert the number of units to int 
        //Deploy* deployOrder = new Deploy(orderName, toDeploy, playerIndex, new int(nUnits));
        Deploy* deployOrder = new Deploy(orderName, toDeployIn, playerId, &nUnits); 
        _orderList->addOrder(deployOrder);

        *_reinforcementPool=*_reinforcementPool-std::stoi(args[1]);

    } else if (args[0] == "advance" && _reinforcementPool==0) { //player should deploy all the units before advancing // more conditions?
        //command : advance 12 iraq iran
        // Advance::Advance(string orderName,int* playerIndex,Territory* advanceFrom,Territory* advanceTo,int* nUnits) - signature
        std::string orderName = args[0];  
        int nUnits = std::stoi(args[1]);
        std::string owned = args[2];
        std::string target = args[3];

        Territory* _owned = findTerritoryByName(owned);
        Territory* _target = findTerritoryByName(target);

        Advance* advanceOrder = new Advance(orderName, playerId, _owned, _target, &nUnits); //territories should be the adjacent territories
        _orderList->addOrder(advanceOrder);

    } else if (args[0] == "blockade" && _reinforcementPool==0) { 
        //command : blockade indonesia
        //Blockade::Blockade(string orderName,int* playerIndex,Territory* toBlock) - Signature
        if (hasCardType("blockade")) {
            std::string orderName = args[0]; 
            std::string target = args[1];
            Territory* _target = findTerritoryByName(target);

            Blockade* blockadeOrder = new Blockade(orderName, playerId, _target); //territories should be the adjacent territories
            _orderList->addOrder(blockadeOrder);
        } else {
            std::cout << "You do not have a blockade card.\n";
        }

    } else if (args[0] == "airlift" && _reinforcementPool==0) {
        //command : airlift 18 indonesia philippines
        //Airlift::Airlift(string orderName,int* playerIndex,Territory* airliftFrom,Territory* airliftTo,int* nUnits) -- Signature
        if (hasCardType("airlift")) {
            std::string orderName = args[0];  
            int nUnits = std::stoi(args[1]);
            std::string owned = args[2];
            std::string target = args[3];

            Territory* _owned = findTerritoryByName(owned);
            Territory* _target = findTerritoryByName(target);
            int* playerIndex = playerId;

            
            Airlift* airliftOrder = new Airlift(orderName, playerIndex, _owned, _target, &nUnits);
            _orderList->addOrder(airliftOrder);
        } else {
            std::cout << "You do not have an Airlift card.\n";
        }

    } else if (args[0] == "negociate" && _reinforcementPool==0) {
        //command : negociate
        // Negotiate::Negotiate(string orderName,int* playerIndex)
        if (hasCardType("diplomacy")) {
            std::string orderName = args[0];
            int* playerIndex = playerId;

            int toNegotiate;

            cout<<"Which player would you like to negotiate with: ";

            cin>>toNegotiate;

            Negotiate* negociateOrder = new Negotiate(orderName, playerIndex, toNegotiate);
            _orderList->addOrder(negociateOrder);
        } else {
            std::cout << "You do not have a Negociate card.\n";
        }

    } else if (args[0] == "bomb" && _reinforcementPool==0) {
        //command : bomb philippines
        // Bomb::Bomb(string orderName,int* playerIndex,Territory* toBomb) -- Signature
        if (hasCardType("bomb")) { 
            std::string orderName = args[0];  
            std::string target = args[1];
            Territory* _target = findTerritoryByName(target);
            int* playerIndex = playerId;

            Bomb* bombOrder = new Bomb(orderName, playerIndex, _target);
            _orderList->addOrder(bombOrder);
        } else {
            std::cout << "You do not have a Bomb card.\n";
        }

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