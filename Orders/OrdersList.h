#pragma once
#include <iostream>
using namespace std;
#include "Orders.h"
class OrdersList{
public:
    //Constructors and Destructors
    OrdersList();
    OrdersList(Order* firstOrder);
    OrdersList(OrdersList* listCopy);
    ~OrdersList();
    //Accessors and Mutators
    Order* getHead();
    Order* getCurrentOrder();
    Order* getTail();
    int getSize();
    void setHead(Order* head);
    void setTail(Order* tail);//This will be implemented if time permits.
    void setCurrentOrder(Order* currentOrder);
    void setSize(int size);
    //methods
    void addOrder(Order* order);//Will add an order to the end of the list.
    void move(int position1,int position2);/*Will seek the position of the order to move. Then will look for the order before position to be move.
    Then but it in between that and the order currently on the position.*/
    void remove(int position);/*Will seek the order before the one to remove, then set the next order to be the order after the one to remove. Delete the order, if the order
    is an order that required a card, put the card back into the players hand*/
    //Assignment Operator
    OrdersList operator=(const OrdersList* ordersList);
private:
    Order* head;//The start of the list.
    Order* tail; //This will be used to add orders and will be good to improve performance of seeking.
    Order* currentOrder; 
    int size;
};

ostream& operator<<(ostream &out,OrdersList *o);