#pragma once
#include "Orders.h"
//Constructors
Order::Order(string orderName,Order* next){
    this->orderName=orderName;
    this->next=next;
}
Order::Order(Order &orderCopy){
    this->orderName=orderCopy.getOrderName();
    this->next=orderCopy.getNext();
}
//Accessors and Mutators
string Order::getOrderName(){
    return orderName;
}

Order* Order::getNext(){
    return next;
}

void Order::setNext(Order &next){
    this->next=&next;
}