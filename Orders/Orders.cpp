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

string Order::getOrderName(){
    return orderName;
}

Order* Order::getNext(){
    return next;
}

Order* Order::getPrevious(){
    return previous;
}

void Order::setNext(Order* next){
    this->next=next;
}

void Order::setOrderName(string orderName){
    this->orderName=orderName;
}

void Order::setPrevious(Order* previous){
    this->previous=previous;
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

//Constructors and Destructors
OrdersList::OrdersList(){
    head=new Order("head");
    tail=new Order("tail");
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
    Order* movedOrder=new Order();   
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