#include <iostream>
using namespace std;
class Order{
private:
	string orderName;
	Order* next;
public:
	//Constructors
	Order();
	Order(string orderName,Order &next);
	Order(Order &orderCopy);
	//methods
	virtual bool validate();/*Checks if the order is capable to execute, the implementation will be defined in the child classes.*/
	virtual void execute();/*Executes the order specified, the implementation will be defined in the child classes.*/
	//Accessors and Mutators
	string getOrderName();
	Order* getNext();
	void setNext(Order* next);
	void setOrderName(string orderName);
};