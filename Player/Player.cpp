//
// Created by Kaoutar El on 2024-09-19.
//

#include "Player.h"
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

Player::Player(){}; 

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
    this->_orderList = other._orderList;
    this->_playerterritories = other._playerterritories;
}

//destructor
Player::~Player()
{
    this->_name.clear();
    this->_territories.clear();
    delete _handCard;
    for (auto order : this->_orderList)
    {
        delete order;
    }
    this->_orderList.clear();
}


// Assignment operator
Player& Player::operator=(const Player& other) {
    if (this == &other) return *this; // Self-assignment check

    // Clear existing data
    for (auto order : this->_orderList) {
        delete order;
    }

    this->_name.clear();
    this->_territories.clear();
    delete _handCard;
    this->_playerterritories.clear();
    this->_orderList.clear();

    // Deep copy the data
    this->_name = other._name;
    this->_territories = other._territories;
    this->_handCard = other._handCard;
    this->_orderList = other._orderList;
    this->_playerterritories = other._playerterritories;

    return *this;
}

// Issue an order
void Player::issueOrder(string order) {
    _orderList.push_back(new string(order)); 
}

// Print the list of orders
void Player::printOrder() const {
    for (const string* order : _orderList) {
        cout << *order << endl;
    }
}

// Return a vector of orders
vector<string*> Player::getOrderList() {
    return _orderList;
}

// Print the hand cards
void Player::printHand() const {
    std::cout << _name << "'s hand cards:\n";
    std::cout << *_handCard;
}

// Returns a list of territories that are to be attacked
void Player::toAttack() const {
    std::cout << _name << " can attack the following territories:\n";
    for (const auto& territory : _territories) {
        // Only show territories not owned by the player
        if (std::find(_playerterritories.begin(), _playerterritories.end(), territory) == _playerterritories.end()) {
            std::cout << *territory << std::endl;
        }
    }
}

// Returns a list of territories that are to be defended
void Player::toDefend() const {
    std::cout << _name << " can defend the following territories:\n";
    for (const auto& territory : _playerterritories) {
        std::cout << *territory << std::endl;
    }
}

// Add a territory to player-owned territories
void Player::addTerritory(Territory* territory) {
    territory->owner=this->_id;
    _playerterritories.push_back(territory);
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