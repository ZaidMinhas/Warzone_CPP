#pragma once
#include <iostream>
using namespace std;
#include "../Map/Map.h"
#include "../LoggingObserver/LoggingObserver.h"

class abOrder{
public:
	abOrder();
	virtual bool validate() = 0;
	virtual void execute() = 0;
};

class Order: virtual public abOrder{
protected:
	string orderName;
	Order* next;
	Order* previous;
	int* playerIndex;
public:
	//Constructors and Destructors
	Order();
	Order(string orderName,int* playerIndex);
	Order(Order* orderCopy);
	~Order();
	//Accessors and Mutators
	string getOrderName();
	Order* getNext();
	Order* getPrevious();
	int* getPlayerIndex();
	void setNext(Order* next);
	void setOrderName(string orderName);
	void setPrevious(Order* previous);
	//methods
	virtual bool validate();/*Checks if the order is capable to execute, the implementation will be defined in the child classes.*/
	virtual void execute();/*Executes the order specified, the implementation will be defined in the child classes.*/
};

class Deploy:virtual public Order, public ILoggable, public Subject{
public:
	Deploy();
	Deploy(string orderName,Territory* toDeploy,int* playerIndex,int* nUnits);
	Deploy(Deploy* deployCopy);
	~Deploy();
	string stringToLog() override;
	bool validate();
	void execute();
	//Accessors
	Territory* getToDeploy();
	int* getNUnits();
	//operator
	Deploy operator=(const Deploy* order);
private:
	Territory* toDeploy;
	int* nUnits;
};

class Advance:virtual public Order, public ILoggable, public Subject{
public:
	Advance();
	Advance(string orderName,int* playerIndex,Territory* advanceFrom,Territory* advanceTo,int* nUnits);
	Advance(Advance* advanceCopy);
	~Advance();
	//Accessors
	Territory* getAdvanceFrom();
	Territory* getAdvanceTo();
	int* getNUnits();
	//methods
	string stringToLog() override;
	bool validate();
	void execute();
	//operator
	Advance operator=(const Advance* order);
private:
	Territory* advanceFrom;
	Territory* advanceTo;
	int* nUnits;
};

class Bomb:virtual public Order{
public:
	Bomb();
	Bomb(string orderName,int* playerIndex,Territory* toBomb);
	Bomb(Bomb* bombCopy);
	~Bomb();
	//Accessors and Mutators
	Territory* getToBomb();
	// string stringToLog() override;
	void setToBomb(Territory* toBomb);
	bool validate();
	void execute();

private:
	Territory* toBomb;
};

class Blockade:virtual public Order , public ILoggable, public Subject{
public:
	Blockade();
	Blockade(string orderName,int* playerIndex,Territory* toBlock);
	Blockade(Blockade* blockadeCopy);
	~Blockade();
	//Accessors
	Territory* getToBlock();
	string stringToLog() override;
	//methods
	bool validate();
	void execute();
private:
	Territory* toBlock;
};

class Airlift:virtual public Order , public ILoggable, public Subject{
public:
	Airlift();
	Airlift(string orderName,int* playerIndex,Territory* airliftFrom,Territory* airliftTo,int* nUnits);
	Airlift(Airlift* airliftCopy);
	~Airlift();
	//Accessors
	Territory* getAirliftFrom();
	Territory* getAirliftTo();
	int* getnUnits();
	string stringToLog() override;
	bool validate();
	void execute();

private:
	Territory* airliftFrom;
	Territory* airliftTo;
	int* nUnits;
};

class Negotiate:virtual public Order, public ILoggable, public Subject{
public:
	Negotiate();
	Negotiate(string orderName,int* playerIndex, int toNegotiate);
	Negotiate(Negotiate* negotiateCopy);
	~Negotiate();
	string stringToLog() override;
	bool validate();
	void execute();
private:
	int toNegotiate;  
};

class Cheat:virtual public Order, public ILoggable, public Subject{
	public:
	Cheat();
	Cheat(string orderName, int* playerIndex);
	Cheat(Cheat* cheatCopy);
	~Cheat();
	string stringToLog() override;
	void execute();
};

class OrdersList : public ILoggable, public Subject{
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
	void addOrder(Deploy* order);//Will add an order to the end of the list.
    void move(int position1,int position2);/*Will seek the position of the order to move. Then will look for the order before position to be move.
    Then but it in between that and the order currently on the position.*/
	bool isEmpty();

    void remove(int position);/*Will seek the order before the one to remove, then set the next order to be the order after the one to remove. Delete the order, if the order
    is an order that required a card, put the card back into the players hand*/
    //operators
	string stringToLog() override;
    OrdersList operator=(const OrdersList* ordersList);
private:
    Order* head;//The start of the list.
    Order* tail; //This will be used to add orders and will be good to improve performance of seeking.
    Order* currentOrder; 
    int size;
};


ostream& operator<<(ostream &out,Order *o);

ostream& operator<<(ostream &out,OrdersList *o);