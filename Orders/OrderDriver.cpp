#include <iostream>
using namespace std;
#include "OrderDriver.h"
#include "Orders.h"
#include "OrdersList.h"
void testOrdersList(){
    OrdersList* test=new OrdersList();
    test->addOrder(new Order("firstOrder"));
    test->addOrder(new Order("SecondOrder"));
    test->addOrder(new Order("ThirdOrder"));
    cout<<test;
    test->remove(2);
    cout<<test;
}