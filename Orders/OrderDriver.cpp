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
    test->addOrder(new Order("Fourth Order"));
    test->addOrder(new Order("Fifth Order"));
    cout<<test;
    test->move(2,4);
    cout<<"Move function terminated successfully"<<endl;
    cout<<test;
}