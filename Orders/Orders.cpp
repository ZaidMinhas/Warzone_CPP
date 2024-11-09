#include <random>
#include <iostream>
using namespace std;
#include "Orders.h"
#include "../Map/Map.h"
#include "../GameEngine/GameEngine.h"
//Constructors and Destructors
abOrder::abOrder(){}

Order::Order():orderName("NA"),next(nullptr),previous(nullptr),playerIndex(0){}

Order::Order(string orderName,int* playerIndex):orderName(orderName),next(nullptr),previous(nullptr),playerIndex(playerIndex){}

Order::Order(Order* orderCopy): orderName(orderCopy->orderName),next(orderCopy->next),previous(orderCopy->previous),playerIndex(playerIndex){}

Order::~Order(){
    delete playerIndex;
    playerIndex = NULL;
    delete next;
    next=NULL;
    delete previous;
    previous=NULL;
}

Deploy::Deploy():Order(),toDeploy(nullptr),nUnits(new int (0)){}

Deploy::Deploy(string orderName,Territory* toDeploy,int* playerIndex,int* nUnits):Order(orderName,playerIndex),toDeploy(toDeploy),nUnits(nUnits){}

Deploy::Deploy(Deploy* deployCopy):Order(deployCopy),toDeploy(deployCopy->toDeploy),nUnits(new int(*(deployCopy->nUnits))){}

Deploy::~Deploy(){}

Advance::Advance():Order(),advanceFrom(nullptr),advanceTo(nullptr),nUnits(new int(0)){}

Advance::Advance(string orderName,int* playerIndex,Territory* advanceFrom,Territory* advanceTo,int* nUnits):Order(orderName,playerIndex),advanceFrom(advanceFrom),advanceTo(advanceTo),nUnits(nUnits){}

Advance::Advance(Advance* advanceCopy):Order(advanceCopy),advanceFrom(advanceCopy->advanceFrom),advanceTo(advanceCopy->advanceTo),nUnits(advanceCopy->nUnits){}

Advance::~Advance(){}

Bomb::Bomb():Order(),toBomb(nullptr){}

Bomb::Bomb(string orderName,int* playerIndex,Territory* toBomb):Order(orderName,playerIndex),toBomb(toBomb){}

Bomb::Bomb(Bomb* bombCopy):Order(bombCopy),toBomb(bombCopy->getToBomb()){}

Blockade::Blockade():Order(),toBlock(nullptr){}

Blockade::Blockade(string orderName,int* playerIndex,Territory* toBlock):Order(orderName,playerIndex),toBlock(toBlock){}

Blockade::Blockade(Blockade* blockadeCopy):Order(blockadeCopy),toBlock(blockadeCopy->toBlock){}

Blockade::~Blockade(){}

Airlift::Airlift():Order(),airliftFrom(nullptr),airliftTo(nullptr){}

Airlift::Airlift(string orderName,int* playerIndex,Territory* airliftFrom,Territory* airliftTo,int* nUnits):Order(orderName,playerIndex),airliftFrom(airliftFrom),airliftTo(airliftTo),nUnits(nUnits){}

Airlift::Airlift(Airlift* airliftCopy):Order(airliftCopy),airliftFrom(airliftCopy->getAirliftFrom()),airliftTo(airliftCopy->getAirliftTo()),nUnits(new int(*(airliftCopy->getnUnits()))){}

Airlift::~Airlift(){}

Negotiate::Negotiate():Order(){}

Negotiate::Negotiate(string orderName,int* playerIndex, int toNegotiate):Order(orderName,playerIndex),toNegotiate(toNegotiate){}

Negotiate::Negotiate(Negotiate* negotiateCopy):Order(negotiateCopy){}

Negotiate::~Negotiate(){}

//Accessors

string Order::getOrderName(){
    return orderName;
}

Order* Order::getNext(){
    return next;
}

Order* Order::getPrevious(){
    return previous;
}

int* Order::getPlayerIndex(){
    return playerIndex;
}

Territory* Deploy::getToDeploy(){
    return toDeploy;
}

int* Deploy::getNUnits(){
    return nUnits;
}

Territory* Advance::getAdvanceFrom(){
    return advanceFrom;
}

Territory* Advance::getAdvanceTo(){
    return advanceTo;
}

int* Advance::getNUnits(){
    return nUnits;
}

Territory* Bomb::getToBomb(){return toBomb;}

Territory* Airlift::getAirliftFrom(){return airliftFrom;}

Territory* Airlift::getAirliftTo(){return airliftTo;}

int* Airlift::getnUnits(){return nUnits;}

//Mutators

void Order::setNext(Order* next){
    this->next=next;
}

void Order::setOrderName(string orderName){
    this->orderName=orderName;
}

void Order::setPrevious(Order* previous){
    this->previous=previous;
}

void Bomb::setToBomb(Territory* toBomb){this->toBomb = toBomb;}

//methods

bool Order::validate(){
    return true;
}

void Order::execute(){}

// ----------------------------------------------------------------
//                     Deploy Order
// ----------------------------------------------------------------

//Deploy order validates if the player has picked his/her territory. If that is the case it will deploy that many units onto the territory.

bool Deploy::validate(){
    if(toDeploy->owner==playerIndex){
        return true;
    }
    return false;
}

void Deploy::execute(){
    if(this->validate()){
        cout<<"Deploying on: "<<toDeploy->name<<endl;
        toDeploy->army= toDeploy->army+*(this->getNUnits());
        cout<<"Puts a certain number of army units on a target territory"<<endl;
    }
    else{
        cout<<"Unable to Deploy on: "<<toDeploy->name<<" for you no longer, or never did, own that territory" <<endl;
    }
}

// ----------------------------------------------------------------
//                     Advance Order
// ----------------------------------------------------------------

/*Advance will validate these things:
*1. If the player owns the territory he/she wants to advance from.
*2. If the territory the player wants to advance to is neighbouring the territory that the player wants to advance from.
*3. If the owner of the territory the player wants to advance to has not executed a negotiate order to the player. (If the player is moving to a territory they own, it will check anyway but it will always be false)
* If any of these conditions are not met. The order will not be executed.
*/

bool Advance::validate(){
    if(advanceFrom->owner!=playerIndex){
        cout<<"Unable to execute Advance order!! You do not own "<<advanceFrom->name<<endl;
        return false;
    }
    else{
        for(auto link : advanceFrom->connections){
           if(link->name==advanceTo->name){
                if(playerList[*(playerIndex)]->negotiation[advanceTo->owner]){
                    cout<<"We have negotiatiated a cease fire on this group commander!! We cannot execute this order!!"<<endl;
                    return false;
                }
                    return true;
           } 
        }
    }
    cout<<"Unable to execute Advance order!! "<<advanceFrom->name<<" does not connect to "<<advanceTo->name<<"!!"<<endl;
    return false;
}

void Advance::execute(){
    if(this->validate()){
        //Will first check if it is advancing on a territory owned by the player, no one, or by an opponent. If no one owns it or its owned by the player. No need for combat.
        if(advanceTo->owner==playerIndex||*(advanceTo->owner)==-1){
            //If the number of units is greater than the number of units the player can advance form the territory, take the whole army and add it into the territory to advance to and set the territory of where the units came from to 0.
            if(nUnits>advanceTo->army){
                *(advanceTo->army)=*(advanceTo->army)+*(advanceFrom->army);
                *(advanceFrom->army) = 0;
            }
            //Otherwise add the units to the territory to advance to, and subtract the same amount from the territory the units came from.
        else{
            *(advanceTo->army)=*(advanceTo->army)+*(nUnits);
            *(advanceFrom->army)=*(advanceFrom->army)-*(nUnits);
            }
        }
        //If its an enemy, combat begins. Setup the attacking units to be the number of units advancing from.
        else{
            cout<<"Entering hostile territory!! Preparing the assault"<<endl;
            *(advanceFrom->army)=*(advanceFrom->army)-*(nUnits);
            int attackingUnits = *(nUnits);
            //Keep doing this loop until one of the sides has not more units to attack with.
            while(attackingUnits!=0 && *(advanceTo->army)!=0){
                //Randomizer to calculate the probability during combat. 60% for the army of the opposing territory to lose a unit, and 70% for the player's army to lose a unit.
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> distrib(1,100);
                if((distrib(gen)<=60)){
                    *(advanceTo->army)=*(advanceTo->army)-1;
                }
                if(distrib(gen)<=70){
                    attackingUnits=attackingUnits-1;
                }
                cout<<"Attacking units remaining: "<<attackingUnits<<endl;
                cout<<"Defending units remaining: "<<*(advanceTo->army)<<endl;
            }
            //Will check who won by seeing who got 0 units first. If both have 0 units, then the defender won.
            if(*(advanceTo->army)==0 && attackingUnits!=0){
                *(advanceTo->owner)=*(playerIndex);
                *(advanceTo->army)=attackingUnits;
                cout<<"The attacking player has succeeded in taking over "<<advanceTo->name<<"!!"<<endl;
                //Update Players owned Territories vector either after executing the function or during.
                gameEngine->CheckWinCon();
            }
            else if(attackingUnits==0){
                cout<<"The defender has successfully drove off the invaders from "<<advanceTo->name<<"!!"<<endl;
            }

        }
    }
}

// ----------------------------------------------------------------
//                     Bomb Order
// ----------------------------------------------------------------

/*In bomb order. If the none of the neighbouring territories to the territory to bomb are owned by the player. Then the player cannot execute the bomb order*/
bool Bomb::validate(){
    for(auto link : toBomb->connections){
        if(*(link->owner)==*(playerIndex)){
            return true;
        }
        cout<<"The opponent you want to bomb is not in the vicinity of a territory you own commander!! We cannot reach that territory to bomb."<<endl;
    }
}
//If bombing target has been validated, it will remove half of the units from that territory
void Bomb::execute(){
    if(this->validate()){
        cout<<"FIRE IN THE HOOOOOOOOOLE!!! "<<toBomb->name<<" will be hit with the bomb and lose half their units!!"<<endl;
        *(toBomb->army) = *(toBomb->army)/2;
    }
    else{
        cout<<"Unable to execute order: "<<this<<endl;
    }
}

// ----------------------------------------------------------------
//                     Blockade Order
// ----------------------------------------------------------------

//Blockade will check if the player owns that territory.
bool Blockade::validate(){
    if(toBlock->owner!=playerIndex){
        cout<<"Commander, "<<toBlock->owner<<" is under enemy command!! We cannot execute the blockade."<<endl;
        return false;
    }
    return true;
}

//If validation is successful, the player will have double the number of units but will no longer own that territory until the round resets in the reinforcement phase.
void Blockade::execute(){
    if(this->validate()){
        cout<<"Initiating Blockade on: "<<toBlock->name<<endl;
        *(toBlock->army) = *(toBlock->army)*2;
        *(toBlock->owner) = -2;
    }
}

// ----------------------------------------------------------------
//                     Airlift Order
// ----------------------------------------------------------------

//Will check if the player owns both the territory to airlift from and the territory to airlift to. If either is not owned by the player, it will not execute.
bool Airlift::validate(){
    if(airliftFrom->owner!=playerIndex){
         cout<<"Commander!! Airlifting is not possible!! We cannot pick them up for "<<airliftFrom->name<<" is controlled by enemy hands!!"<<endl;
        return false;
    }
    else if(airliftTo->owner!=playerIndex){
        cout<<"Commander!! Airlifting is not possible!! We cannot drop them off at for "<<airliftTo->name<<" is controlled by enemy hands!!"<<endl;
        return false;
    }
    return true;
}

//If it validates successfully, it will move the number of units from the territory to airlift from to the territory to airlift to.

void Airlift::execute(){
    if(this->validate()){
        cout<<"Airlifting "<<*(nUnits)<<" units from "<<airliftFrom->name<<" to "<<airliftTo->name<<"!!!"<<endl;
        //If the number of units is greater than the number of units the player can airlift form the territory, take the whole army and add it into the territory to airlift to and set the territory of where the units came from to 0.
        if(*(nUnits)>*(airliftFrom->army)){
            *(airliftTo->army) = *(airliftTo->army) + *(airliftFrom->army);
            *(airliftFrom->army) = 0;
        }
        //else airlift the number of units asked in the issueing phase.
        else{
            *(airliftTo->army) = *(airliftTo->army) + *(nUnits);
            *(airliftFrom->army) = *(airliftFrom->army) - *(nUnits);
        }
    }
}

// ----------------------------------------------------------------
//                     Negotiate Order
// ----------------------------------------------------------------

//Negotiate will check if the player is not negotiating with the himself/herself.

bool Negotiate::validate(){
    if(toNegotiate==*(playerIndex)){
        cout<<"Commander!! Have you gone mad?! We cannot issue a negotiate order with yourself!!"<<endl;
        return false;
    }
    return true;
}

//If validated successfully, the player will go into the game engines player list and set the negotiation index of the player who issued the order to be true. That way the opposing player that was targeted cannot attack tha player who issued the order.

void Negotiate::execute(){
    if(this->validate()){
        //Find the player to negotiate with in the players negotiate array and set it to true
        playerList[toNegotiate]->negotiation[playerIndex] = true;
    }
}

//operators

Deploy Deploy::operator=(const Deploy *order)
{
    this->next=order->next;
    this->previous=order->previous;
    this->playerIndex=order->playerIndex;
    this->toDeploy=order->toDeploy;
    this->nUnits=order->nUnits;
    return this;
}

Advance Advance::operator=(const Advance *order)
{
    this->next = order->next;
    this->previous = order->previous;
    this->playerIndex = order->playerIndex;
    this->advanceFrom = order->advanceFrom;
    this->advanceTo = order->advanceTo;
    this->nUnits = order->nUnits;
    return this;
}

ostream& operator<<(ostream &out, Order *o){
    out<<o->getOrderName();
    return out;
}

//Constructors and Destructors
OrdersList::OrdersList(){
    head = new Order();
    tail = new Order();
    head->setNext(tail);
    tail->setPrevious(head);
    size=0;
}

OrdersList::OrdersList(Order *firstOrder){
    head->setNext(firstOrder);
    tail->setPrevious(firstOrder);
    firstOrder->setPrevious(head);
    firstOrder->setNext(tail);
    size=1;
}

OrdersList::OrdersList(OrdersList* listCopy){
    this->head=listCopy->head;
    this->tail=listCopy->tail;
    this->size=listCopy->size;
}

OrdersList::~OrdersList(){
    delete currentOrder;
    currentOrder=NULL;
    delete head;
    head=NULL;
    delete tail;
    tail=NULL;
}

//Accessors and Mutators
Order* OrdersList::getHead(){
    return head;
}

Order* OrdersList::getCurrentOrder(){
    return currentOrder;
}

// Method to get the next order in the list relative to currentOrder - K - A2
Order* OrdersList::getNextOrder() {
    if (currentOrder != nullptr && currentOrder->getNext() != tail) {
        return currentOrder->getNext();
    }
    return nullptr;  // return nullptr if there is no next order
}

Order* OrdersList::getTail(){
    return tail;
}

int OrdersList::getSize(){
    return size;
}

void OrdersList::setHead(Order* head){
    this->head=head;
}

void OrdersList::setTail(Order* tail){
    this->tail=tail;
}

void OrdersList::setCurrentOrder(Order* currentOrder){
    this->currentOrder=currentOrder;
}

void OrdersList::setSize(int size){
    this->size=size;
}

//methods
//Will add an order to the end of the list
void OrdersList::addOrder(Order* newOrder){
    if(size==0){
        head->setNext(newOrder);
        tail->setPrevious(newOrder);
        newOrder->setPrevious(head);
        newOrder->setNext(tail);
    }
    else{
       //Step 1:set next of newOrder to tail.
        newOrder->setNext(tail);
        newOrder->setPrevious(tail->getPrevious());
        tail->getPrevious()->setNext(newOrder);
        tail->setPrevious(newOrder);
    }
    size++;
}

void OrdersList::remove(int position){
    //Step 1: Check base cases to make sure removal is possible: out of bounds.
    if(position<1||position>this->getSize()){
        cout<<"Position of order to remove is out of bounds"<<endl;
    }
    else{
        cout<<"Roger that! Removing order "<<position<< "from the list"<<endl;
        //Step 2: Seek the position of the order to remove.
        currentOrder=head->getNext();
        for(int i=1;i<=this->getSize();i++){
            if(i==position){
                //Step 3: Check if order needed a card to execute, if it did return it to player (Part 2)
                //Step 4: Set the next of the previous order to the next of the order to remove.
                currentOrder->getPrevious()->setNext(currentOrder->getNext());
                currentOrder->getNext()->setPrevious(currentOrder->getPrevious());
                //Step 6: Deconstruct order
                currentOrder->setNext(nullptr);
                currentOrder->setPrevious(nullptr);
                size--;
                break;
            }
            currentOrder=currentOrder->getNext();
        }
        currentOrder=head->getNext();

    }
}

void OrdersList::move(int position1,int position2){
    Order* movedOrder;   
    //Check base cases for position1 and position2: out of bounds, same positions are called.
    if((position1<1||position1>this->getSize())||(position2<1||position2>this->getSize())){
        cout<<"Positions of orders asked for are out of bounds"<<endl;
    }
    else if(position1==position2){
        cout<<"Same position called!!"<<endl;
    }
    else{
        cout<<"Roger Roger!! Moving order "<<position1<<" to order "<<position2<<endl;
        //Find the order that needs to be moved, keep track of the order to be moved using movedOrder, and connect the orders before and after together. 
        setCurrentOrder(head->getNext());
        for(int i=1;i<=getSize();i++){
            if(i==position1){
                movedOrder=currentOrder;
                currentOrder->getPrevious()->setNext(currentOrder->getNext());
                currentOrder->getNext()->setPrevious(currentOrder->getPrevious());
                break;
            }
            setCurrentOrder(currentOrder->getNext());
        }
        setCurrentOrder(head->getNext());
        //Find the position the order wants to be moved to. and put it in between two orders so its in the new position
        for(int i=1;i<=this->size;i++){
            if(i==position2){
                movedOrder->setPrevious(currentOrder->getPrevious());
                movedOrder->setNext(currentOrder);
                movedOrder->getPrevious()->setNext(movedOrder);
                movedOrder->getNext()->setPrevious(movedOrder);
                break;
            }
            currentOrder=currentOrder->getNext();
        }
    }
    
}

//operators
OrdersList OrdersList::operator=(const OrdersList* ordersList){
        if(this!=ordersList){
            this->head=ordersList->head;
            this->tail=ordersList->tail;
            this->size=ordersList->size;
        }
        return this;
    }

ostream& operator<<(ostream &out,OrdersList *o){
    if(o->getSize()==0){
        out<<"Order list is empty";
        return out;
    }
    else{
        o->setCurrentOrder(o->getHead()->getNext());
        out<<"Here is your list of current orders Commander:"<<endl;
        for(int i=1;i<=o->getSize();i++){
            out<<"("<<i<<") "<<o->getCurrentOrder()<<endl;
            o->setCurrentOrder(o->getCurrentOrder()->getNext());
        }
    }
    return out;
};