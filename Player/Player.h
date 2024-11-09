#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>  // to use std::string
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"

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
    
    // Function to find a territory by name -- needed to issue the order
    Territory* findTerritoryByName(const std::string& territoryName);
    
    //std::vector<Territory*> findTerritoryByName(const std::string& territoryName, const std::vector<Territory*>& territories) const;
    void issueOrder(const std::string& command, int* playerId);
    
    // custom function to add a territory to the player's owned territories
    void addTerritory(Territory* territory);
    
    // if a card exists in the player's hand by its name
    bool hasCardType(const std::string& cardType);

    // check if the player has more orders to issue
    bool hasMoreOrders() const;


    
    // --------------------------------------------------
    //                  Getters/Setters
    // --------------------------------------------------
    
    OrdersList* getOrdersList(); // changed - K - A2
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
    std::vector<bool> negotiation;
    bool* _doneTurn;

private:
    int* _id;
    std::string _name;
    std::vector<Territory*> _territories;
    std::vector<Territory*> _playerterritories;
    OrdersList* _orderList;  // Changed to OrdersList pointer - K - A2
    Hand* _handCard; //moved to private - A2 - K
    std::vector<std::string> _handCards;  // Vector of card names
};

extern std::vector<Player*> playerList;
std::ostream& operator <<(std::ostream &out, Player &player);

#endif
