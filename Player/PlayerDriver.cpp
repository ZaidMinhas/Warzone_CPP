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
    /*std::cout << "\nTerritories owned by " << player1->getName() << ":\n";
    for (const auto& territory : player1->getTerritories()) { // Assuming getTerritories() returns a vector<Territory*>
        //std::cout << territory->getName() << std::endl; // Print only the name of each territory
        std::cout << *territory << std::endl;
        std::cout<<"\n";
    } -- works but doesn't call toDefend()*/


    std::cout << "\nTerritories to defend by " << player1->getName() << ":\n";
    std::vector<Territory*> territoriesToDefend = player1->toDefend();  // use the updated version of toDefend() to get the territories
    if (territoriesToDefend.empty()) {
        std::cout << "No territories to defend." << std::endl;
    } else {
        for (const auto& territory : territoriesToDefend) {
            std::cout << *territory << std::endl;  // Print each territory the player can defend
        }
    } 

    // list of attackable territories
    std::cout << "\nTerritories to attack by " << player1->getName() << ":\n";
    std::vector<Territory*> territoriesToAttack = player1->toAttack();  // territories the player can attack

    // display them
    if (territoriesToAttack.empty()) {
        std::cout << "No territories available to attack." << std::endl;
    } else {
        std::cout << "Select a territory to attack by entering the corresponding number:\n";
        for (size_t i = 0; i < territoriesToAttack.size(); ++i) {
            std::cout << "\n - Territory number " << i + 1 << "\n" << *territoriesToAttack[i] << std::endl;
        }
    }


    //Attack simulation
    int choice;
    std::cout << "Enter the territory you want to attack (1 to " << territoriesToAttack.size() << "): ";
    std::cin >> choice;

    // Validate the user's choice
    if (choice >= 1 && choice <= territoriesToAttack.size()) {
        Territory* selectedTerritory = territoriesToAttack[choice - 1];
        std::cout << "You selected: \n" << *selectedTerritory << std::endl;
        
        // attack logic for the selected territory -> issue order
        // (Call the appropriate method to issue the attack order)
    } else {
        std::cout << "Invalid choice. Please select a valid territory." << std::endl;
    }


}


