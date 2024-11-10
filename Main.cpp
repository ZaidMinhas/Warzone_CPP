#include <iostream>
#include "CommandProcessor\CommandProcessingDriver.h"
#include "Map\MapDriver.h"
#include "GameEngine\GameEngineDriver.h"
//#include "Player\PlayerDriver.h"
#include "Orders\OrderDriver.h"
#include "Cards\CardsDriver.h"
int main(int argc, char *argv[])
{	

	//testMap();
	//testPlayer();
	//testOrdersList();
    //testCards();

	//Part 1 PLEASE DONT TOUCH
	testCommandProcessor(argv);

	testStartupPhase();

	//GameEngineDriver.cpp => GameEngine.cpp
	testMainGameLoop();

	//OrderDriver.cpp
	testOrderExecution();
	
	std::string s;
	std::cin>>s;
	return 0;
}


