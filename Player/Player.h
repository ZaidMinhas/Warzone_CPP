#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>  // to use std::string
#include "..\Orders\OrdersList.h"
#include "..\Map\Map.h"
#include "..\Cards\Cards.h"

class Player {

public:
    // Default constructor
    Player();
    
    // Constructor with only name and id
    Player(const std::string &name, int* id);

    // Copy constructor
    Player(const Player&);

    // Destructor
    ~Player();

    // Member functions
    void toAttack() const;
    void toDefend() const;
    void issueOrder(const std::string& orderName); // changed - K - A2
    OrdersList* getOrderList(); // changed - K - A2
    //void issueOrder(std::string);
    //std::vector<std::string*> getOrderList();
    std::string getName() const;
    void setHand(Hand* hand); // changed - K - A2
    Hand* getHand();

    int getID();

    void printOrder() const;
    // Function to print hand cards -- optional just to show player's hand
    void printHand() const;
    
    // Custom function to add a territory to the player's owned territories
    void addTerritory(Territory* territory);
    std::vector<Territory*> getTerritories() const;  // New method to get owned territories - K - A2

    //Operator
    Player& operator = (const Player& player);
    int*  _reinforcementPool;

private:
    int* _id;
    std::string _name;
    std::vector<Territory*> _territories;
    std::vector<Territory*> _playerterritories;
    OrdersList* _orderList;  // Changed to OrdersList pointer - K - A2
    Hand* _handCard; //moved to private - A2 - K
};

extern std::vector<Player*> playerList;
std::ostream& operator <<(std::ostream &out, Player &player);

#endif
