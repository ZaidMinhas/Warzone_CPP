#include "Player.h"  // Include the Player class definition
#include "..\Map\Map.h" // Include the Map class definition
#include "..\Cards\Cards.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib> // For rand and srand
#include <ctime>   // For time

void testPlayer() {
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (gameMap.loadMap("Map/Asia.map") != 0) {
        std::cout << "Failed to load map." << std::endl;
        return;
    } //--ok

    // Display the contents of gameMap.graph
    /*std::cout << "Territories in the map:\n";
    for (const Territory& territory : gameMap.graph) {
        std::cout << territory << std::endl; 
    }*/ //-- ok

    // draw 3 cards from the deck into the hand -- make it random ~later
    Deck deck;
    Hand* hand = new Hand(); // empty hand
    std::cout << "\nSystem is drawing 3 cards from the deck for the player's hand...\n";
    for (int i = 0; i < 3; ++i) {
        deck.draw(*hand);
    } //--ok

    // Instantiate Player 
    int* playerId = new int(1);
    Player* player1 = new Player("Player K", playerId);

    // Assign the hand created above to the player
    player1->setHand(hand);

    // Randomly assign territories to the player - using random Index
    int numTerritoriesToAssign = 3; // 3 teritorries for each new player
    for (int i = 0; i < numTerritoriesToAssign; ++i) {
        int randomIndex = std::rand() % gameMap.graph.size(); 
        player1->addTerritory(&gameMap.graph[randomIndex]);  
    }

    // Print player's hand
    std::cout << "\n" << player1->getName() << "'s hand cards:\n";
    std::cout << *hand;  // Print hand contents

    // Display the names of territories owned by the player
    std::cout << "\nTerritories owned by " << player1->getName() << ":\n";
    for (const auto& territory : player1->getTerritories()) { // Assuming getTerritories() returns a vector<Territory*>
        //std::cout << territory->getName() << std::endl; // Print only the name of each territory
        std::cout << *territory << std::endl;
    }

}


