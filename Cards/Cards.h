#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <queue>
#include <map>
class Hand;
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
    Cards();
    Cards(const Cards& cards);
    Cards play();

    Cards &operator=(const Cards &other);

    friend std::ostream& operator<<(std::ostream& os, const Cards& c);

private:
    std::string card;
};

//-----------------------------------------------------------------------

class Deck {
public:
    Deck();
    Deck(int size);
    Deck(const Deck& deck);
    void draw(Hand& hand);
    void addCard(const Cards & card);


    friend std::ostream& operator<<(std::ostream& os, const Deck& d);



private:
    void fillDeck();

    Deck &operator=(const Deck &other);

    int size;
    std::queue<Cards> cards;
};

//----------------------------------------------------------------------

class Hand {
public:
    Hand();
    Hand(int size);
    Hand(const Hand& hand);
    bool isHandFull();
    void play(Deck& deck, int i);
    void addCard(const Cards &card);

    Hand &operator=(const Hand &other);

    friend std::ostream& operator<<(std::ostream& os, const Hand& h);

private:
    int size;
    std::vector<Cards> cards;

};


#endif //CARDS_H
