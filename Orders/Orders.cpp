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

Negotiate::Negotiate(string orderName,int* playerIndex):Order(orderName,playerIndex){}

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

bool Advance::validate(){
    if(advanceFrom->owner!=playerIndex){
        cout<<"Unable to execute Advance order!! You do not own "<<advanceFrom->name<<endl;
        return false;
    }
    /*If the player is attacking a player that has played the negatiate order on them,
     cout<<"Commander, we have made a peace treaty with <<advanceTo->owner<< this round!! We cannot invade their territory!!"<<endl;
     return false*/
    else{
        for(auto link : advanceFrom->connections){
           if(link->name==advanceTo->name){
                return true;
           } 
        }
    }
    cout<<"Unable to execute Advance order!! "<<advanceFrom->name<<" does not connect to "<<advanceTo->name<<"!!"<<endl;
    return false;
}

void Advance::execute(){
    if(this->validate()){
        if(advanceTo->owner==playerIndex||*(advanceTo->owner)==-1){
            //Add validation for nUnits. if advanceFrom->army<nUnits. advanceFrom->army is transfered instead.
            if(nUnits>advanceTo->army){
                *(advanceTo->army)=*(advanceTo->army)+*(advanceFrom->army);
                *(advanceFrom->army) = 0;
            }
        else{
            *(advanceTo->army)=*(advanceTo->army)+*(nUnits);
            *(advanceFrom->army)=*(advanceFrom->army)-*(nUnits);
            }
        }
        else{
            cout<<"Entering hostile territory!! Preparing the assault"<<endl;
            *(advanceFrom->army)=*(advanceFrom->army)-*(nUnits);
            int attackingUnits = *(nUnits);
            while(attackingUnits!=0 && *(advanceTo->army)!=0){
                //Randomizer to calculate the probability during combat.
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

            if(*(advanceTo->army)==0 && attackingUnits!=0){
                *(advanceTo->owner)=*(playerIndex);
                *(advanceTo->army)=attackingUnits;
                cout<<"The attacking player has succeeded in taking over "<<advanceTo->name<<"!!"<<endl;
                //Update Players owned Territories vector either after executing the function or during.
            }
            else if(attackingUnits==0){
                cout<<"The defender has successfully drove off the invaders from "<<advanceTo->name<<"!!"<<endl;
            }

        }
    }
}

//Will work with Kaoutar to determine how to update player's owned order list after advancing/Blockading
void Bomb::execute(){
    if(this->validate()){
        cout<<"Executing order: "<<this<<endl;
        cout<<"Destroys half of the army units located on a target territory. This order can only be issued if a player has the bomb card in their hand."<<endl;
    }
    else{
        cout<<"Unable to execute order: "<<this<<endl;
    }
}
bool Blockade::validate(){
    if(toBlock->owner!=playerIndex){
        cout<<"Commander, "<<toBlock->owner<<" is under enemy command!! We cannot execute the blockade."<<endl;
        return false;
    }
    return true;
}

void Blockade::execute(){
    if(this->validate()){
        cout<<"Initiating Blockade on: "<<toBlock->name<<endl;
        *(toBlock->army) = *(toBlock->army)*2;
        *(toBlock->owner) = -2;
    }
}

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

void Airlift::execute(){
    if(this->validate()){
        cout<<"Airlifting "<<*(nUnits)<<" units from "<<airliftFrom->name<<" to "<<airliftTo->name<<"!!!"<<endl;
        if(*(nUnits)>*(airliftFrom->army)){
            *(airliftTo->army) = *(airliftTo->army) + *(airliftFrom->army);
            *(airliftFrom->army) = 0;
        }
        else{
            *(airliftTo->army) = *(airliftTo->army) + *(nUnits);
            *(airliftFrom->army) = *(airliftFrom->army) - *(nUnits);
        }
    }
}

void Negotiate::execute(){
    if(this->validate()){
        cout<<"Executing order: "<<this<<endl;
        cout<<"prevent attacks between the current player and another target player until the end of the turn. This"<<endl;
        cout<<"order can only be issued if a player has the diplomacy card in their hand."<<endl;
    }
    else{
        cout<<"Unable to execute order: "<<this<<endl;
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