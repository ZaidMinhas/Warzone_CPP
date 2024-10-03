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
//operators
ostream& operator<<(ostream &out, Order *o){
    out<<o->getOrderName();
    return out;
}