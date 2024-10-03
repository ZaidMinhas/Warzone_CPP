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

class Deploy:public Order{
public:
	Deploy(string orderName);
	void execute();
};

class Advance:public Order{
public:
	Advance(string orderName);
	void execute();
};

class Bomb:public Order{
public:
	Bomb(string orderName);
	void execute();
};

class Blockade:public Order{
public:
	Blockade(string orderName);
	void execute();
};

class Airlift:public Order{
public:
	Airlift(string orderName);
	void execute();
};

class Negotiate:public Order{
public:
	Negotiate(string orderName);
	void execute();
};

ostream& operator<<(ostream &out,Order *o);