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
    firstOrder->setPrevious(head);
    firstOrder->setNext(tail);
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
        cout<<"Removing order "<<position<<endl;
        //Step 2: Seek the position of the order to remove.
        currentOrder=head->getNext();
        for(int i=1;i<=this->getSize();i++){
            if(i==position){
                //Step 3: Check if order needed a card to execute, if it did return it to player (Part 2)
                //Step 4: Set the next of the previous order to the next of the order to remove.
                currentOrder->getPrevious()->setNext(currentOrder->getNext());
                currentOrder->getNext()->setPrevious(currentOrder->getPrevious());
                //Step 6: Deconstruct order (ask TA or prof before submitting)
                currentOrder->setNext(nullptr);
                currentOrder->setPrevious(nullptr);
                size--;
                break;
            }
            currentOrder=currentOrder->getNext();
        }

    }
}

void OrdersList::move(int position1,int position2){
    //Step 1:Check base cases for position1 and position2, out of bounds, same positions are called.
    if((position1<1||position1>this->getSize())||(position2<1||position2>this->getSize())){
        cout<<"Positions of orders asked for are out of bounds"<<endl;
    }
    else if(position1==position2){
        cout<<"Same position called!!"<<endl;
    }
    else{
        cout<<"Moving order "<<position1<<" to order "<<position2<<endl;
    }
    //Step 2:Find the order that wants to be moved (position 1).
    //Step 3:Keep track of that order, then change the next of the previous order to the next of the current order.
    //Step 4:Change the previous of the next order to the previous of the current order.
    //Step 5:Find the position2 that the order wants to be moved to.
    //Step 6:
    //Step 4: 
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