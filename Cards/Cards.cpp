#include "Cards.h"
#include <queue>
#include <iostream>
#include <cstdlib>
#include <map>
using namespace std;
using std::string;


//Cards class
Cards::Cards(){}; //default constructor

Cards::Cards(int cKey){
    this->cardType = cards_Key.at(cKey); //assigns type to card
}

string Cards:: getcardType(){
    return *cardType;
}


void Cards::play(){

}

//Deck object = contains finite collection of cards
Deck::Deck(){
    this->maxCards = new int(5);
}

int Deck:: getmaxCards(){
    return *maxCards;
}

//Fills deck with finite ammount of cards
int Deck::fillDeck(){
    //fills  with random cards
    for(int i = 0; i < getmaxCards(); i++){
       int randomNumber = 1 + rand() % 5;
       Cards* tempCard = new Cards(randomNumber);
       _gameDeck.push(tempCard);
    }
}

Cards Deck::draw(){
    Cards* drawnCard = _gameDeck.front();
    _gameDeck.pop();
}


//Hand object = is a finite collection of cards 


/*
int main(){}
*/

