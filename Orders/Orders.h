#pragma once
#include <iostream>
using namespace std;
class Order{
protected:
	string orderName;
	Order* next;
	Order* previous;
	int size;
public:
	//Constructors and Destructors
	Order();
	Order(string orderName);
	Order(Order* orderCopy);
	~Order();
	//Accessors and Mutators
	string getOrderName(){return orderName;}
	Order* getNext(){return next;};
	Order* getPrevious(){return previous;}
	void setNext(Order* next){this->next=next;}
	void setOrderName(string orderName){this->orderName=orderName;}
	void setPrevious(Order* previous){this->previous=previous;}
	//methods
	virtual bool validate();/*Checks if the order is capable to execute, the implementation will be defined in the child classes.*/
	virtual void execute();/*Executes the order specified, the implementation will be defined in the child classes.*/
};

ostream& operator<<(ostream &out,Order *o);