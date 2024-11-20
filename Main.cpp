#include <iostream>
#include <string>

#include "PlayerStrategies/PlayerStrategiesDriver.h"
#include "CommandProcessor/CommandProcessingDriver.h"
#include "GameEngine/GameEngineDriver.h"
#include "LoggingObserver/LoggingObserverDriver.h"
int main(int argc, char *argv[])
{
	testLoggingObserver();
	testCommandProcessor(argv, argc);
	testStartupPhase();
	testMainGameLoop();

	// testPlayerStrategies();
	
	std::string s;
	std::cin>>s;
	return 0;
}


