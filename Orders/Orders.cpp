#include <iostream>
using namespace std;
#include "Orders.h"

Order::Order(){
    orderName="N/A";
    next=nullptr;
}

string Order::getOrderName(){
    return orderName;
}