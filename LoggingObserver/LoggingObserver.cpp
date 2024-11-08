//
// Created by minha on 11/8/2024.
//

#include "LoggingObserver.h"
#include <iostream>
#include <fstream>


void Subject::addObserver(Observer *observer) {
  _observer = observer;
}

void Subject::Notify(ILoggable& loggable){
	_observer->Update(loggable);
}

LoggingObserver::LoggingObserver(){

  std::ofstream myfile;
  myfile.open("gamelog.txt");
  myfile.close();
}


void LoggingObserver::Update(ILoggable& loggable){
	string log = loggable.stringToLog();
  	std::ofstream myfile;
    myfile.open("gamelog.txt", std::ios_base::app);
    myfile << log;
    myfile.close();
}

LoggingObserver* loggingObserver = new LoggingObserver();