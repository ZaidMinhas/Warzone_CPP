#include "Orders.h"
#include <iostream>
#include <string>
using namespace std;
void testOrdersList(){
    Order* test=new Order();
    cout<<"Working on "<<test->orderName<<endl;
}

int main(){
    testOrdersList();
}