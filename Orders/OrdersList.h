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
    void setHead(Order* head);
    void setCurrentOrder(Order* currentOrder);
    //methods
    void addOrder(Order* order);//Will add an order to the beginning of the list.
    void move(int position1,int position2);
    void remove();
    void toString();
private:
    Order* head;
    Order* currentOrder; 
};