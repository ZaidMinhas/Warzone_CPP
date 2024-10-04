#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Cards.h"
#include "CardsDriver.h"

void testCards() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Deck* deck = new Deck();
    Hand* hand = new Hand();

    bool gameOver = false;

    while (!gameOver) {
        std::cout << "1: View Deck\n";
        std::cout << "2: View Hand\n";

        std::cout << "3: Draw Card from Deck\n";
        std::cout << "4: Play Card from Hand\n";

        std::cout << "5: Exit\n";
        string input;
        std::cin >> input;

        if (input == "1") {
            std::cout << *deck;
        }
        else if (input == "2") {
            std::cout << *hand;
        }
        else if (input == "3") {
            deck->draw(*hand);
        }
        else if (input == "4") {
            std::cout << "Pick a card from your hand:\n";
            std::cout << *hand;
            int card;
            std::cout << ": ";
            std::cin >> card;
            hand->play(*deck, card);
        }
        else if (input == "5") {
            gameOver = true;
        }
        else {
            std::cout << "Invalid input\n\n";
        }
    }

    delete deck;
    delete hand;


}

// int main()
// {
//     testCards();
//     return 0;
// }
