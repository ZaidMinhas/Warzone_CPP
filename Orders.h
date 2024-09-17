#include <string>
using namespace std;
class Order{
public:
	//Constructors
	Order();
	Order(string orderName);
	Order(Order &orderCopy);
	//methods
	virtual bool validate();
	virtual void execute();
	//Accessors and Mutators
	string getOrderName();
	Order* getNext();
	Order* getPrevious();
	void setNext(Order &order);
	void setPrevious(Order &previous);
private:
	string orderName;
	Order* next;
	Order* previous;
};