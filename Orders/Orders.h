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
	string getOrderName();
	Order* getNext();
	Order* getPrevious();
	void setNext(Order* next);
	void setOrderName(string orderName);
	void setPrevious(Order* previous);
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
    //operators
    OrdersList operator=(const OrdersList* ordersList);
private:
    Order* head;//The start of the list.
    Order* tail; //This will be used to add orders and will be good to improve performance of seeking.
    Order* currentOrder; 
    int size;
};

ostream& operator<<(ostream &out,Order *o);

ostream& operator<<(ostream &out,OrdersList *o);