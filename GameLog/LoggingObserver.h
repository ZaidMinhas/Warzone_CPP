//def ndef

#pragma once
#include <list>
using namespace std;

//iLoggable

// Observer
class Observer {
	public: ~Observer();
    virtual void Update() = 0;
    //virtual void Update(ILoggable i);
    
    protected; 
    	Observer(); 

};

//Subject, all must be subclasses of Subject
class Subject {
	public:
    	virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify();
        //virtual void Notify(ILoggable i);
        
        Subject();
        ~Subject();
        
    private:
    	list<Observer*> *_observers;
};

//log interface, alllllll our classes must be subclssd/inherit this one too
class ILoggable() {
	public:
    	virtual string stringToLog() = 0; //returns string to be outputted to log file
        
        ILoggable();

};
























































