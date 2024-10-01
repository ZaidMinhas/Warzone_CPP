#include "Orders.h"
//Constructors
Order::Order(){
    orderName="N/A";
    next=nullptr;
}

Order::Order(string orderName){
    this->orderName=orderName;
}
//methods
bool Order::validate(){
    return true;
}

void Order::execute(){
    cout<<"Executing order: "<<getOrderName()<<endl;
}
//operators
ostream& operator<<(ostream &out, Order *o){
    out<<"Order: "<<o->getOrderName();
    return out;
}