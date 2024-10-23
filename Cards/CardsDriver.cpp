#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Cards.h"


void testCards(){
        
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        Deck* deck = new Deck(); //auto fills deck
        Hand* hand =new Hand();

        std::cout << *deck << "\n";
        std::cout << *hand << "\n";;

        //draws cards to hand
        while(!hand->isHandFull()){
            // std::cout << "LOOPY" << std::endl;
            deck->draw(*hand);
            // break;
        }
        std::cout << std::endl;
        int handSize = hand->getHandSize();
        //plans cards and returns to deck
        for (int playedCard = 0; playedCard < handSize; playedCard++){
            hand->play(*deck, 0);
        }
        std::cout << std::endl;
        std::cout << *deck << "\n";
        std::cout << *hand << "\n";;

   }
   

// int main(){
//
//     testCards();
//     return 0;
// }
