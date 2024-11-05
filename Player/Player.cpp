
#include "Player.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include "..\Orders\OrdersList.h"


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

void Player::issueOrder(const string& orderName) { // changed - K - A2
    Order* newOrder = new Order(orderName);  // Create a new order
    _orderList->addOrder(newOrder);          // Add the new order to the actual OrdersList
}

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

// Returns a list of territories that are to be attacked
/*void Player::toAttack() const {
    std::cout << _name << " can attack the following territories:\n";
    for (const auto& territory : _territories) {
        // Only show territories not owned by the player
        if (std::find(_playerterritories.begin(), _playerterritories.end(), territory) == _playerterritories.end()) {
            std::cout << *territory << std::endl;
        }
    }
}*/


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



// Returns a list of territories that are to be defended
/*void Player::toDefend() const {
    std::cout << _name << " can defend the following territories:\n";
    for (const auto& territory : _playerterritories) { // Each time the player concquer a territory, it should be added in _playerTerritory
        std::cout << *territory << std::endl;
    }
}*/

//Defend changed - K - A2
std::vector<Territory*> Player::toDefend() const {
    std::vector<Territory*> territoriesToDefend;

    // Add all player-owned territories to the vector
    for (const auto& territory : _playerterritories) { // Each time the player concquer a territory, it should be added in _playerTerritory
        territoriesToDefend.push_back(territory);
    }

    return territoriesToDefend;
}

// Add a territory to player-owned territories
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