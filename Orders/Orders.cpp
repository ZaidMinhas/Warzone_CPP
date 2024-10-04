#include <cmath>
#include "Orders.h"
//Constructors and Destructors
Order::Order(){
    orderName="N/A";
    next=nullptr;
}

Order::Order(string orderName){
    this->orderName=orderName;
}

Order::Order(Order* orderCopy){
    this->orderName=orderCopy->orderName;
    this->next=orderCopy->next;
    this->previous=orderCopy->previous;
}

Order::~Order(){
    delete next;
    next=NULL;
    delete previous;
    previous=NULL;
}

Deploy::Deploy(string orderName):Order(orderName){}

Advance::Advance(string orderName):Order(orderName){}

Bomb::Bomb(string orderName):Order(orderName){}

Blockade::Blockade(string orderName):Order(orderName){}

Airlift::Airlift(string orderName):Order(orderName){}

Negotiate::Negotiate(string orderName):Order(orderName){}

//methods
bool Order::validate(){
    int random = rand()%10 + 1;
    if(random<=5){
        return false;
    }
    return true;
}

void Order::execute(){
    if(this->validate()){
        cout<<"Executing order: "<<this<<endl;
    }
    else{
        cout<<"Unable to execute order: "<<this<<endl;
    }
}

void Deploy::execute(){
    if(this->validate()){
        cout<<"Executing order: "<<this<<endl;
        cout<<"Puts a certain number of army units on a target territory"<<endl;
    }
    else{
        cout<<"Unable to execute order: "<<this<<endl;
    }
}

void Advance::execute(){
    if(this->validate()){
        cout<<"Executing order: "<<this<<endl;
        cout<<"moves a certain number of army units from one territory (source territory) to another territory (target territory)"<<endl;
    }
    else{
        cout<<"Unable to execute order: "<<this<<endl;
    }
}

void Bomb::execute(){
    if(this->validate()){
        cout<<"Executing order: "<<this<<endl;
        cout<<"Destroys half of the army units located on a target territory. This order can only be issued if a player has the bomb card in their hand."<<endl;
    }
    else{
        cout<<"Unable to execute order: "<<this<<endl;
    }
}

void Blockade::execute(){
    if(this->validate()){
        cout<<"Executing order: "<<this<<endl;
        cout<<"Triples the number of army units on a target territory and makes it a neutral territory. This order can only be issued if a player has the blockade card in their hand."<<endl;
    }
    else{
        cout<<"Unable to execute order: "<<this<<endl;
    }
}

void Airlift::execute(){
    if(this->validate()){
        cout<<"Executing order: "<<this<<endl;
        cout<<"Advances a certain number of army units from one from one territory (source territory) to another"<<endl;
        cout<<"territory (target territory). This order can only be issued if a player has the airlift card in their hand."<<endl;
    }
    else{
        cout<<"Unable to execute order: "<<this<<endl;
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
Order Order::operator=(const Order *order)
{
    if(this!=order){
        this->orderName=order->orderName;
        this->next=order->next;
        this->previous=order->previous;
    }
    return this;
}

ostream& operator<<(ostream &out, Order *o){
    out<<o->getOrderName();
    return out;
}