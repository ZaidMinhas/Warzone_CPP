#include <string>
using namespace std;
class Order{
public:
	//Constructors
	Order();
	Order(string orderName,Order* next);
	Order(Order &orderCopy);
	//methods
	virtual bool validate();//Will validate if the order can be executed during the order phase and the execution phase.
	virtual void execute();//executes the order, this will be implemented in the subclasses
	virtual string toString(); //Returns the details of the order to the player
	//Accessors and Mutators
	string getOrderName();
	Order* getNext();
	void setNext(Order* next);
	
private:
	string orderName;
	Order* next;
};