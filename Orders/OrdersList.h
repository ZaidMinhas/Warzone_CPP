#include <string>
using namespace std;
#include "Orders.h"
class OrdersList{
public:
    //Constructors
    OrdersList();
    OrdersList(Order &firstOrder);
    OrdersList(OrdersList &list);
    //Accessors and Mutators
    Order* getHead();
    Order* getCurrentOrder();
    int getSize();
    void setHead(Order* head);
    void setCurrentOrder(Order* currentOrder);
    //methods
    void addOrder(Order* order);//Will add an order to the end of the list.
    void move(int oldposition,int newPosition);//Seeking the old position of the order and move it to the new position and putting it in between the order before and the order thats in the current position.
    void remove(int position);//Seeking the order of the position and removing it from the list, if it is an order that requires a card, the card gets refunded.
    void toString();//Displays all the orders in the players list.
private:
    Order* head;
    Order* currentOrder;
    int size; 
};