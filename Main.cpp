#include <iostream>
#include <string>
#include <cstdlib>
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
	
	system("pause");
	/*std::string s;
	std::cin>>s;*/
	return 0;
}


