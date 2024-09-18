#include <string>
using namespace std;
class Order{
public:
	//Constructors
	Order(string orderName,Order* next);
	Order(Order &orderCopy);
	//methods
	virtual bool validate();
	virtual void execute();
	//Accessors and Mutators
	string getOrderName();
	Order* getNext();
	void setNext(Order &next);
private:
	string orderName;
	Order* next;
};