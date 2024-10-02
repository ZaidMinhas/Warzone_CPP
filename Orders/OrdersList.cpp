#include "OrdersList.h"
//Constructors and Destructors
OrdersList::OrdersList(){
    head=new Order();
    tail=new Order();
    head->setNext(tail);
    size=0;
}

OrdersList::OrdersList(Order *firstOrder){
    head->setNext(firstOrder);
    tail->setPrevious(firstOrder);
    size=1;
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
    //Step 1: Get tail. Step 2:set next of tail to newOrder. Step3: make new order the tail.
    if(size==0){
        head->setNext(newOrder);
        tail->setPrevious(newOrder);
    }
    else{
        newOrder->setNext(tail);
        newOrder->setPrevious(tail->getPrevious());
        tail->getPrevious()->setNext(newOrder);
    }
    size++;
}

ostream& operator<<(ostream &out,OrdersList *o){
    if(o->getSize()==0){
        out<<"Order list is empty";
        return out;
    }
    else{
        o->setCurrentOrder(o->getHead()->getNext());
        out<<"Here is your list of current orders:"<<endl;
        for(int i=1;i<=o->getSize();i++){
            out<<"("<<i<<")"<<o->getCurrentOrder()<<endl;
            o->setCurrentOrder(o->getCurrentOrder()->getNext());
        }
    }
    return out;
};