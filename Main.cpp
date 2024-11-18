#include <iostream>
#include <string>

#include "PlayerStrategies/PlayerStrategiesDriver.h"
#include "CommandProcessor/CommandProcessingDriver.h"


int main(int argc, char *argv[])
{	
	testCommandProcessor(argv, argc);
	testPlayerStrategies();
	
	std::string s;
	std::cin>>s;
	return 0;
}


