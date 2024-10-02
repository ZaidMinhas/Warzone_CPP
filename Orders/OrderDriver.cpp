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
    cout<<test->getSize();
    cout<<test<<endl;
    test->setCurrentOrder(test->getHead()->getNext());
    for(int i=1;i<=test->getSize();i++){
        test->getCurrentOrder()->execute();
        test->setCurrentOrder(test->getCurrentOrder()->getNext());
    }
}