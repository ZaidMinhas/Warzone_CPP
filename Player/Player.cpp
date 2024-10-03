//
// Created by Kaoutar El on 2024-09-19.
//

#include "Player.h"
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;


Player::Player(const string &name, const vector<string*> &territory, const vector<string*> &hand, const vector<string*> &order)
{
    this->_name = name;
    this->_territory = territory;
    this->_handCard = hand;
    this->_orderList = order;
}

//player reference
Player::Player(const Player& p)
{
    this->_name = p._name;
    this->_territory = p._territory;
    this->_handCard = p._handCard;
    this->_orderList = p._orderList;
}

//destructor
Player::~Player()
{
    this->_name.clear();
    this->_territory.clear();
    this->_handCard.clear();
    for (auto order : this->_orderList)
    {
        delete order;
    }
    this->_orderList.clear();
}

// Issue an order
void Player::issueOrder(string order) {
    _orderList.push_back(new string(order)); // Add a new order to the list
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

// Define the toAttack method
void Player::toAttack() const {
    cout << _name << " is planning to attack." << endl;
}

// Define the toDefend method
void Player::toDefend() const {
    cout << _name << " is planning to defend." << endl;
}


