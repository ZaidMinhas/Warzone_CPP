#include <cmath>
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