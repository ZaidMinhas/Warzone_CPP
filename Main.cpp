#include <iostream>
#include "CommandProcessor/CommandProcessingDriver.h"
#include "LoggingObserver/LoggingObserverDriver.h"
#include "Map/MapDriver.h"
#include "GameEngine/GameEngineDriver.h"
//#include "Player\PlayerDriver.h"
#include "Orders/OrderDriver.h"
#include "Cards/CardsDriver.h"

int main(int argc, char *argv[])
{	

	//testMap();
	//testPlayer();
	//testOrdersList();
    //testCards();
	//PART 5 DO NOT CHANGE ORDER
	testLoggingObserver();
	//Part 1 PLEASE DONT TOUCH
	testCommandProcessor(argv, argc);

	testStartupPhase();

	//GameEngineDriver.cpp => GameEngine.cpp
	testMainGameLoop();

	//OrderDriver.cpp
	testOrderExecution();
	
	std::string s;
	std::cin>>s;
	return 0;
}


