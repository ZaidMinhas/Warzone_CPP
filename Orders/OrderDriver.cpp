#include <iostream>
using namespace std;
#include "Orders.h"
#include "OrdersList.h"
int testOrdersList(){
    OrdersList* test=new OrdersList();
    Order* orderTest=new Order();
    Order* firstOrder=new Order("firstOrder");
    test->addOrder(firstOrder);
    test->addOrder(new Order("secondOrder"));
    cout<<"testOrdersList is working."<<endl;
    test->setCurrentOrder(test->getHead()->getNext());
    cout<<test->getCurrentOrder()->getOrderName()<<endl;
    test->setCurrentOrder(test->getCurrentOrder()->getNext());
    cout<<test->getCurrentOrder()->getOrderName()<<endl;
    return 0;
}

int main(){
    int test = testOrdersList();
    return test;
}