#include "Player.h"  // Include the Player class definition
#include <vector>
#include <string>


void testPlayer() {
    //printf("This is the player driver");

    // Create territories and hands using raw pointers
     std::vector<std::string*> territories;
     territories.push_back(new std::string("Japan"));
     territories.push_back(new std::string("Korea"));
     territories.push_back(new std::string("Brazil"));
     territories.push_back(new std::string("Cuba"));

    // All the territories 
    for (const auto& territory : territories) {
        printf("%s\n", territory->c_str());  
    }

    // Cleanup
    for (auto territory : territories) {
        delete territory;
    }

    std::vector<std::string*> hand;
     hand.push_back(new std::string("Bomb Card"));
     hand.push_back(new std::string("Reinforcement Card"));
     hand.push_back(new std::string("Blockade Card"));
     //hand.push_back(new std::string("Airlift Card"));
     //hand.push_back(new std::string("Diplomacy Card"));

    
    std::vector<std::string*> orders; // Start with an empty list of orders
    //orders.push_back(new std::string("Order 1"));
    //orders.push_back(new std::string("Order 2"));

    // Instantiate a Player object using dynamic allocation
    Player* player1 = new Player("Player K", territories, hand, orders);
    
    // Automatically assign the first 3 territories to the player's owned territories - mock 
    for (size_t i = 0; i < 3 && i < territories.size(); ++i) {
        player1->addTerritory(territories[i]);
    }

    // Print the territories owned by the player
    //std::cout << "\nPlayer K owns the following territories:\n";
    player1->toDefend();  // Player can only defend the territories owned

    // Get player input for attack or defense
    std::string action;
    std::cout << "Enter 'attack' or 'defend': ";
    std::cin >> action;

    if (action == "attack") {
        player1->toAttack(); // Player can attack territories not owned
        std::cout << "Issuing an attack order...\n";
        player1->issueOrder("Attack");
    } else if (action == "defend") {
        player1->toDefend(); // Player can defend owned territories
        std::cout << "Issuing a defend order...\n";
        player1->issueOrder("Defend");
    } else {
        std::cout << "Invalid action. Please enter 'attack' or 'defend'.\n";
    }

    // Display all issued orders
    std::cout << "\nOrders issued by " << player1->getName() << ":\n";
    player1->printOrder();  // Print the issued orders - mock order object


}

