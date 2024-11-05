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

    // --------------------------------------------------
    //          Member functions of player
    // --------------------------------------------------
    //void toAttack() const;
    //vector<Territory*> toAttack(vector<Territory*>); // changed - K - A2
    std::vector<Territory*> toAttack() const;
    std::vector<Territory*> toDefend() const;
    //void issueOrder(const std::string& orderName);
    // Updated issueOrder signature
    void issueOrder(const std::string& orderName, 
                    const std::vector<Territory*>& availableTerritoriesToDefend, 
                    const std::vector<Territory*>& attackableTerritories); // changed
    // Custom function to add a territory to the player's owned territories
    void addTerritory(Territory* territory);
    
    // --------------------------------------------------
    //                  Getters/Setters
    // --------------------------------------------------
    
    OrdersList* getOrderList(); // changed - K - A2
    std::string getName() const;
    Hand* getHand();
    std::vector<Territory*> getTerritories() const;  // New method to get owned territories - K - A2
    int getID();
    void setHand(Hand* hand); // changed - K - A2

    // --------------------------------------------------
    //                  Display tests
    // --------------------------------------------------
    void printOrder() const;
    // Function to print hand cards -- optional just to show player's hand
    void printHand() const;
    
   
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
