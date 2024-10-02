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
    cout<<test<<endl;
}