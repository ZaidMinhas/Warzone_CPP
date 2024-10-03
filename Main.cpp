#include <iostream>
#include "Map\MapDriver.h"
#include "GameEngine\GameEngineDriver.h"
#include "Player\PlayerDriver.h"
#include "Orders\OrderDriver.h"
int main(int argc, char **argv)
{
	testMap();
	testPlayer();
	testGameStates();
	testOrdersList();
	std::string s;
	std::cin>>s;
	return 0;
}
