#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <queue>
#include <map>
using std::string;

//Types of cards you can get
const std::map<int, std::string> cards_Key = {
    {1, "bomb"},
    {2, "reinforcement"},
    {3, "blockade"},
    {4, "airlift"},
    {5, "diplomacy"}
};

class Cards{

    public: 

        string *cardType;
        string getcardType();

        void play();

        Cards(int ckey);
        Cards();

};


class Deck{

    public:

        queue<Cards *> _gameDeck;

        int *maxCards;
        int getmaxCards();
        
        int fillDeck(); //fills deck with random cards
        
        Cards draw(); //gets placed into player's hand

        Deck(int maxCards);
        Deck();
};


class Hand{
    
};


/*
free function
testCards()
- creates a deck of all kinds of cards
- creates a hand object
- fills up hand object by drawing from deck 
- calls play for each card in hand 
    (cards get returned to deck)
*/

#endif