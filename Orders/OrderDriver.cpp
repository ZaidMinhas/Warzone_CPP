#include <iostream>
using namespace std;
#include "Orders.h"
int testOrdersList(){
    Order* test=new Order();
    cout<<"testOrdersList is working."<<endl;
    cout<<"Order Name: "<<test->getOrderName()<<endl;
    return 0;
}

int main(){
    int test = testOrdersList();
    return test;
}