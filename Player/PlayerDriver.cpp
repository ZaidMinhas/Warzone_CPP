#include "Player.h"  // Include the Player class definition
#include "..\Map\Map.h" // Include the Map class definition
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib> // For rand and srand
#include <ctime>   // For time

void testPlayer() {
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (gameMap.loadMap("../Map/Asia.map") != 0) {
        std::cout << "Failed to load map." << std::endl;
        return;
    }

    // Display the contents of gameMap.graph
    std::cout << "Territories in the map:\n";
    for (const Territory& territory : gameMap.graph) {
        std::cout << territory << std::endl; // Assuming operator<< is overloaded for Territory
    }

}


