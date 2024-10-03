#include "Player.h"  // Include the Player class definition
#include <vector>
#include <string>


void testPlayer() {
    //printf("This is the player driver");

    // Create territories and hands using raw pointers
     std::vector<std::string*> territories;
     territories.push_back(new std::string("Territory1"));
     territories.push_back(new std::string("Territory2"));

        // Print the territories using printf
    for (const auto& territory : territories) {
        printf("%s\n", territory->c_str());  // Use c_str() to convert std::string to C-style string
    }

    // Cleanup: Don't forget to delete the allocated strings
    for (auto territory : territories) {
        delete territory;
    }

    std::vector<std::string*> hand;
     hand.push_back(new std::string("Card1"));
     hand.push_back(new std::string("Card2"));

    
    std::vector<std::string*> orders; // Start with an empty list of orders
    orders.push_back(new std::string("Order 1"));
    orders.push_back(new std::string("Order 2"));

    std::string name = "Player K";

    // Instantiate a Player object using the parameterized constructor
    Player player1(name, territories, hand, orders);
    
    // Issue some orders
    player1.issueOrder("Attack Territory1");
    player1.issueOrder("Defend Territory2");

    // Print orders
    std::cout << "Orders for " << player1.getName() << ":\n";  // Now getName() should exist
    player1.printOrder();

    // Demonstration
    player1.toAttack();  // This should print that the player is planning to attack
    player1.toDefend();  // This should print that the player is planning to defend

    // Cleanup: You need to free the dynamically allocated strings
    for (auto territory : territories) {
        delete territory;
    }
    for (auto card : hand) {
        delete card;
    }

}


// void testPlayer()
// {
//     // Create territories and hands using raw pointers
//     std::vector<std::string*> territories;
//     territories.push_back(new std::string("Territory1"));
//     territories.push_back(new std::string("Territory2"));

//     std::vector<std::string*> hand;
//     hand.push_back(new std::string("Card1"));
//     hand.push_back(new std::string("Card2"));

//     std::vector<std::string*> orders; // Start with an empty list of orders

//     // Create a Player
//     Player player1("Player 1", territories, hand, orders);

//     // Issue some orders
//     player1.issueOrder("Attack Territory1");
//     player1.issueOrder("Defend Territory2");

//     // Print orders
//     std::cout << "Orders for " << player1.getName() << ":\n";  // Now getName() should exist
//     player1.printOrder();

//     // Demonstrate attack and defend methods
//     player1.toAttack();  // This should print that the player is planning to attack
//     player1.toDefend();  // This should print that the player is planning to defend

//     // Cleanup: You need to free the dynamically allocated strings
//     for (auto territory : territories) {
//         delete territory;
//     }
//     for (auto card : hand) {
//         delete card;
//     }

// }
