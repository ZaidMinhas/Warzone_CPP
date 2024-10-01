#include <iostream>
using namespace std;
#include "OrderDriver.h"
#include "Orders.h"
#include "OrdersList.h"
void testOrdersList(){
    OrdersList* test=new OrdersList();
    Order* orderTest=new Order();
    Order* firstOrder=new Order("firstOrder");
    test->addOrder(firstOrder);
    test->addOrder(new Order("secondOrder"));
    cout<<"testOrdersList is working."<<endl;
    test->setCurrentOrder(test->getHead()->getNext());
    cout<<test->getCurrentOrder()<<endl;
    test->setCurrentOrder(test->getCurrentOrder()->getNext());
    cout<<test->getCurrentOrder()<<endl;
}