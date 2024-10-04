#include "Cards.h"
#include <queue>
#include <iostream>
#include <cstdlib>
#include <map>
using namespace std;
using std::string;
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()


Cards::Cards(){

    int index  = 1 + rand() % 5;
    card = cards_Key.at(index);
}

Cards::Cards(const Cards &cards) {
    card=cards.card;
}

Cards Cards::play() {
    cout << "Playing " << card << "\n\n";

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Cards& c) {
    os << c.card << " card";
    return os;
}

Cards& Cards::operator=(const Cards& other) {
    if (this != &other) { // Check for self-assignment
        card = other.card; // Perform a deep copy of the string
    }
    return *this; // Return the current object
}

//-----------------------------DECK---------------------------------

Deck::Deck(): size(5) {
    fillDeck();

}

Deck::Deck(int size) {
    this->size = size;
    fillDeck();
}

Deck::Deck(const Deck &deck) {
    size = deck.size;
    cards = deck.cards;

}

void Deck::addCard(const Cards &card) {
    cards.push(card);
}

void Deck::draw(Hand &hand) {
    if (!cards.empty() && !hand.isHandFull()) {
        Cards card = cards.front();
        cout << card << " was drawn from the deck\n";
        cards.pop();
        hand.addCard(card);
    }
    else {
        if (cards.empty()) {
            cout << "Deck is full";
        }
        else {
            cout << "Hand is full";
        }
    }
}

void Deck::fillDeck() {
    for (int i = 0; i < size; i++) {
        Cards card;
        cards.push(card);
    }
}

std::ostream& operator<<(std::ostream& os, const Deck& d) {
    std::queue<Cards> deckCopy = d.cards;
    cout << "Cards in deck: " << endl;
    while (!deckCopy.empty()) {

        os << "  " << deckCopy.front() << endl;
        deckCopy.pop();
    }
    os << "\n";
    return os;
}

Deck& Deck::operator=(const Deck& other) {
    if (this != &other) { // Check for self-assignment
        size = other.size; // Copy size
        cards = other.cards; // Copy the queue
    }
    return *this; // Return the current object
}

//--------------------------------------HAND-------------------------------------

Hand::Hand() : size(10) {
}

Hand::Hand(int size) {
    this->size = size;
}

Hand::Hand(const Hand &hand) {
    size = hand.size;
    cards = hand.cards;
}


bool Hand::isHandFull() {
    return size == cards.size();
}

void Hand::play(Deck& deck, int i) {
    Cards card = cards[i].play();
    cards.erase(cards.begin() + i);
    deck.addCard(card);
}

void Hand::addCard(const Cards &card) {
    cards.push_back(card);
}

std::ostream& operator<<(std::ostream& os, const Hand& h) {
    cout << "Card in hands: " << endl;
    for (int i = 0; i < h.cards.size(); i++) {
        os << "  " << i << ": " <<  h.cards[i] << endl;
    }
    os << "\n";

    return os;
}
Hand& Hand::operator=(const Hand& other) {
    if (this != &other) { // Check for self-assignment
        size = other.size; // Copy size
        cards = other.cards; // Copy the vector
    }
    return *this; // Return the current object
}
