#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>  // to use std::string
#include "../Map/Map.h"
#include "../Cards/Cards.h"

class Player {

public:
    // Default constructor
    Player();
    
    // Parameterized constructor
    //Player(const std::string &name, const std::vector<std::string*> &territories, const std::vector<std::string*> &hand, const std::vector<std::string*> &orders);

    // Constructor with only name and id
    Player(const std::string &name, int* id);

    // Copy constructor
    Player(const Player&);

    // Destructor
    ~Player();

    // Member functions
    void toAttack() const;
    void toDefend() const;
    void issueOrder(std::string);
    std::vector<std::string*> getOrderList();
    std::string getName() const;
    void printOrder() const;
    // Function to print hand cards -- optional just to show player's hand
    void printHand() const;
    
    // Custom function to add a territory to the player's owned territories
    void addTerritory(Territory* territory);

    //Operator
    Player& operator = (const Player& player);


    int*  _reinforcementPool;
    Hand* _handCard;
    int* _id;
private:
    std::string _name;
    std::vector<Territory*> _territories;
    std::vector<Territory*> _playerterritories;
    std::vector<std::string*> _orderList;
    
};

extern std::vector<Player*> playerList;
std::ostream& operator <<(std::ostream &out, Player &player);

#endif
