#include "Orders.h"
//Constructors
Order::Order(){
    orderName="N/A";
    next=nullptr;
}

Order::Order(string orderName){
    this->orderName=orderName;
}
//Accessors and Mutators
string Order::getOrderName(){
    return orderName;
}

Order* Order::getNext(){
    return next;
}

Order* Order::getPrevious(){
    return previous;
}

void Order::setPrevious(Order* previous){
    this->previous=previous;
}

void Order::setNext(Order* next){
    this->next=next;
}

void Order::setOrderName(string orderName){
    this->orderName=orderName;
}
//methods
bool Order::validate(){
    return true;
}

void Order::execute(){
    cout<<"Executing order: "<<getOrderName()<<endl;
}