#pragma once
#include <iostream>
using namespace std;
class Order{
private:
	string orderName;
	Order* next;
	Order* previous;
public:
	//Constructors
	Order();
	Order(string orderName);
	//methods
	virtual bool validate();/*Checks if the order is capable to execute, the implementation will be defined in the child classes.*/
	virtual void execute();/*Executes the order specified, the implementation will be defined in the child classes.*/
	//Accessors and Mutators
	string getOrderName();
	Order* getNext();
	Order* getPrevious();
	void setNext(Order* next);
	void setOrderName(string orderName);
	void setPrevious(Order* previous);
};