#include <iostream>
#include <string>
#include "PlayerStrategies/PlayerStrategiesDriver.h"
#include "CommandProcessor/CommandProcessingDriver.h"
#include "GameEngine/TournamentDriver.h"
#include "LoggingObserver/LoggingObserverDriver.h"
int main(int argc, char *argv[])
{

	//######## MUST STAY ACTIVE #######
	testLoggingObserver();
	testCommandProcessor(argv, argc);
	//#################################


	// testPlayerStrategies();
	testTournament();
	
	std::string s;
	std::cin>>s;
	return 0;
}


