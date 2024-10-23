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
	//operators
	Order operator=(const Order* order);
};

class Deploy:public Order{
public:
	Deploy();
	Deploy(string orderName);
	Deploy(Deploy* deployCopy);
	~Deploy();
	void execute();
};

class Advance:public Order{
public:
	Advance();
	Advance(string orderName);
	Advance(Advance* advanceCopy);
	~Advance();
	void execute();
};

class Bomb:public Order{
public:
	Bomb();
	Bomb(string orderName);
	Bomb(Bomb* bombCopy);
	~Bomb();
	void execute();
};

class Blockade:public Order{
public:
	Blockade();
	Blockade(string orderName);
	Blockade(Blockade* blockadeCopy);
	~Blockade();
	void execute();
};

class Airlift:public Order{
public:
	Airlift();
	Airlift(string orderName);
	Airlift(Airlift* airliftCopy);
	~Airlift();
	void execute();
};

class Negotiate:public Order{
public:
	Negotiate();
	Negotiate(string orderName);
	Negotiate(Negotiate* negotiateCopy);
	~Negotiate();
	void execute();
};

ostream& operator<<(ostream &out,Order *o);