#include <iostream>
#include "CommandProcessor\CommandProcessor.h"
#include "Map\MapDriver.h"
#include "GameEngine\GameEngineDriver.h"
//#include "Player\PlayerDriver.h"
#include "Orders\OrderDriver.h"
#include "Cards\CardsDriver.h"
int main(int argc, char *argv[])
{	
	if(argc==1||argv[1]=="-console"){
		commandProcessor = CommandProcessor();
	}else if(argc==3||argv[1]=="-file"){
		commandProcessor = FileCommandProcessorAdapter(argv[2]);
	}
	//testMap();
	//testPlayer();
	//testOrdersList();
    //testCards();
	testStartupPhase();
	testMainGameLoop();
	
	std::string s;
	std::cin>>s;
	return 0;
}


