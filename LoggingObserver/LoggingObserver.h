//
// Created by minha on 11/8/2024.
//

#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H
#include <iostream>

using std::string;

class ILoggable{
public:
    virtual ~ILoggable() = default;
    virtual string stringToLog() = 0;

};

class Observer{
public:
    virtual ~Observer() = default;
    virtual void Update(ILoggable& loggable) = 0;

};

class Subject{
    private:
    Observer* _observer = nullptr;
    public:
    void addObserver(Observer* observer);
    protected:
    void Notify( ILoggable& loggable);
};



class LoggingObserver: public Observer{
    public:
    LoggingObserver();
    void Update(ILoggable& loggable) override;

};


//Subscriber used by all classes
extern LoggingObserver* loggingObserver;

#endif //LOGGINGOBSERVER_H
