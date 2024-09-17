#include <string>
using namespace std;
#include "Orders.h"
class OrdersList{
public:
    //Constructors
    OrdersList();
    OrdersList(Order* headOrder);
    OrdersList(OrdersList &list);
    //methods
    void move(string direction);
    void remove();
    void toString();
private:
    Order* currentOrder; 
};