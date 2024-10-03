#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>  // to use std::string

class Player {

public:
    // Default constructor
    Player();
    
    // Parameterized constructor
    Player(const std::string &name, const std::vector<std::string*> &territory, const std::vector<std::string*> &hand, const std::vector<std::string*> &order);

    // Copy constructor
    Player(const Player&);

    // Destructor
    ~Player();

    // Member functions
    void toAttack() const;
    void toDefend() const;
    void issueOrder(std::string);
    std::vector<std::string*> getOrderList();
    std::string getName(){
        return _name;
    }
    void printOrder() const;

private:
    std::string _name;
    std::vector<std::string*> _territory;
    std::vector<std::string*> _handCard;
    std::vector<std::string*> _orderList;
};

#endif
