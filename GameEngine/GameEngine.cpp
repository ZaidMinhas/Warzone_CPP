//
// Created by minha on 10/2/2024.
//

#include "GameEngine.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>
#include <vector>
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../CommandProcessor/CommandProcessor.h"
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

State::State() {}
State::State(State &state) {}
State &State::operator=(const State &other)
{
    return *this;
}

//--------------------START STATE--------------------

State *Start::clone()
{
    return new Start();
}

// handle input takes in the input command and game_engine that the state may use to change game behavior
State *Start::handleInput(GameEngine &game_engine, std::string &input)
{
    if (input == "loadmap")
    {
        string fileName;
        cin >> fileName;
        std::cout << "\n"
                  << fileName << "\n";
        if (gameMap.loadMap(fileName) == 0)
        {
            return new MapLoaded();
        }
        else
        {
            return new Start();
        }
    }
    return nullptr;
}

// run when a state reaction is finalized
void Start::enter(GameEngine &game_engine)
{
    cout << "Entering Start State\n"
         << endl;
    cout << "Commands: loadmap\n\n";
}
// run before a state is deleted
void Start::exit(GameEngine &game_engine)
{
    cout << "\nExiting Start State" << endl;
}

//--------------------MAP LOADER STATE--------------------

State *MapLoaded::clone()
{
    return new MapLoaded();
}

State *MapLoaded::handleInput(GameEngine &game_engine, std::string &input)
{
    if (input == "loadmap")
    {
        string fileName;
        cin >> fileName;
        std::cout << "\n"
                  << fileName << "\n";
        if (gameMap.loadMap(fileName) == 0)
        {
            return new MapLoaded();
        }
        else
        {
            return new Start();
        }
    }
    if (input == "validatemap")
    {
        if (gameMap.validate() == 0)
        {
            return new MapValidated();
        }
        else
        {
            return new Start();
        }
    }
    return nullptr;
}

void MapLoaded::enter(GameEngine &game_engine)
{
    cout << "Entering MapLoaded State\n"
         << endl;
    cout << "Commands: loadmap, validatemap\n\n";
}

void MapLoaded::exit(GameEngine &game_engine)
{
    cout << "\nExiting MapLoaded State" << endl;
}

//--------------------MAP VALIDATED STATE--------------------

State *MapValidated::clone()
{
    return new MapValidated();
}

State *MapValidated::handleInput(GameEngine &game_engine, std::string &input)
{
    if (input == "addplayer")
    {
        string name;
        cin >> name;
        playerList.push_back(new Player());
        return new PlayersAdded();
    }
    return nullptr;
}

void MapValidated::enter(GameEngine &game_engine)
{
    cout << "Entering MapValidated State\n"
         << endl;
    cout << "Commands: addplayer\n\n";
}

void MapValidated::exit(GameEngine &game_engine)
{
    cout << "\nExiting MapValidated State" << endl;
}

//--------------------PLAYERS ADDED STATE--------------------

State *PlayersAdded::clone()
{
    return new PlayersAdded();
}

State *PlayersAdded::handleInput(GameEngine &game_engine, std::string &input)
{
    if (input == "addplayer")
    {
        string name;
        cin >> name;
        playerList.push_back(new Player());
        return new PlayersAdded();
    }

    if (input == "gamestart")
    {
        gameEngine.gamestart();
        return new AssignReinforcement();
    }

    if (input == "assigncountries")
    {
        return new AssignReinforcement();
    }
    return nullptr;
}

void PlayersAdded::enter(GameEngine &game_engine)
{
    cout << "Entering PlayersAdded State\n"
         << endl;
    cout << "Commands: addplayer, assigncountries\n\n";
}

void PlayersAdded::exit(GameEngine &game_engine)
{
    cout << "\nExiting PlayersAdded State" << endl;
}

//--------------------ASSIGN REINFORCEMENT STATE--------------------

State *AssignReinforcement::clone()
{
    return new AssignReinforcement();
}

State *AssignReinforcement::handleInput(GameEngine &game_engine, std::string &input)
{
    if (input == "issueorder")
    {
        return new IssueOrders();
    }
    return nullptr;
}

void AssignReinforcement::enter(GameEngine &game_engine)
{
    cout << "Entering AssignReinforcement State\n"
         << endl;
    cout << "Commands: issueorder\n\n";
}

void AssignReinforcement::exit(GameEngine &game_engine)
{
    cout << "\nExiting AssignReinforcement State" << endl;
}

//--------------------ISSUE ORDERS STATE--------------------
State *IssueOrders::clone()
{
    return new IssueOrders();
}

State *IssueOrders::handleInput(GameEngine &game_engine, std::string &input)
{
    if (input == "issueorder")
    {
        return new IssueOrders();
    }
    if (input == "endissueorders")
    {
        return new ExecuteOrders();
    }
    return nullptr;
}

void IssueOrders::enter(GameEngine &game_engine)
{
    cout << "Entering IssueOrders State\n"
         << endl;
    cout << "Commands: issueorder, endissueorders\n\n";
}

void IssueOrders::exit(GameEngine &game_engine)
{
    cout << "\nExiting IssueOrders State" << endl;
}

//--------------------EXECUTE ORDERS STATE--------------------
State *ExecuteOrders::clone()
{
    return new ExecuteOrders();
}

State *ExecuteOrders::handleInput(GameEngine &game_engine, std::string &input)
{
    if (input == "execorder")
    {
        return new ExecuteOrders();
    }
    if (input == "endexecorders")
    {
        return new AssignReinforcement();
    }

    if (input == "win")
    {
        return new Win();
    }
    return nullptr;
}

void ExecuteOrders::enter(GameEngine &game_engine)
{
    cout << "Entering ExecuteOrders State\n"
         << endl;
    cout << "Commands: execorder, endexecorders, win\n\n";
}

void ExecuteOrders::exit(GameEngine &game_engine)
{
    cout << "\nExiting ExecuteOrders State" << endl;
}

//--------------------WIN STATE--------------------
State *Win::clone()
{
    return new Win();
}

State *Win::handleInput(GameEngine &game_engine, std::string &input)
{
    if (input == "end")
    {
        game_engine.setGameOver(true);
        return new End();
    }
    if (input == "play")
    {
        return new Start();
    }
    return nullptr;
}

void Win::enter(GameEngine &game_engine)
{
    cout << "Entering Win State\n"
         << endl;
    cout << "Commands: end, play\n\n";
}

void Win::exit(GameEngine &game_engine)
{
    cout << "\nExiting Win State" << endl;
}

//--------------------END STATE--------------------
State *End::clone()
{
    return new End();
}

State *End::handleInput(GameEngine &game_engine, std::string &input)
{
    return nullptr;
}

void End::enter(GameEngine &game_engine)
{
    cout << "Entering End State\n"
         << endl;
    //    cout << "Commands: end, play\n\n";
}

void End::exit(GameEngine &game_engine)
{
    cout << "\nExiting End State" << endl;
}

std::ostream &operator<<(std::ostream &os, const State &state)
{
    os << "Current State: " << state.getName();
    return os;
}

// ##############################################################################//
GameEngine gameEngine = GameEngine();
//--------------------GAME ENGINE--------------------
GameEngine::GameEngine()
{
    addObserver(loggingObserver);
    showingTournament = false;
    gameOver = false;
    currentState = new Start();
}

GameEngine::GameEngine(GameEngine *gameEngine)
{
    addObserver(loggingObserver);
    showingTournament = gameEngine->showingTournament;
    gameOver = gameEngine->gameOver;
    currentState = gameEngine->currentState ? gameEngine->currentState->clone() : nullptr;
}

void GameEngine::setGameOver(bool b) { gameOver = b; }

void GameEngine::run()
{
    cout << "Welcome to Warzone\n" << endl;
    while (!gameOver) {
        startupPhase();
        mainGameLoop();
    }
    if (tournamentMode) {
        showingTournament = true;
        cout << getResults();
        Notify(*this);

        winners.clear();
    }
    cout << "Thank you for playing!" << endl;

    /*while (true)
    {
        cout << "Enter command:";
        cin >> command;
        handleInput(command);

        if (gameOver)
        {
            cout << "Game has ended!" << endl;
            break;
        }
    }*/
}

void GameEngine::handleInput(std::string &input)
{
    State *nextState = currentState->handleInput(*this, input);

    if (nextState != nullptr)
    {
        currentState->exit(*this);

        delete currentState;
        currentState = nextState;

        currentState->enter(*this);
    }
    else
    {
        cout << "INCORRECT COMMAND\n"
             << endl;
    }
}

void GameEngine::transition(State *state)
{
    delete currentState;
    this->currentState = state;
    Notify(*this);
}


string GameEngine::stringToLog() {
    if (showingTournament) {
        return getResults();
    }
    else {
        return "GameEngine new state: " + getCurrentState();
    }

}


string GameEngine::getCurrentState()
{
    return this->currentState->getName();
}

std::ostream &operator<<(std::ostream &os, const GameEngine &engine)
{
    os << *engine.currentState << ".\nIs the game over: " << (engine.gameOver == true ? "YES" : "NO");
    return os;
}

GameEngine &GameEngine::operator=(const GameEngine &other)
{
    if (this != &other)
    {

        delete currentState;
        currentState = other.currentState ? other.currentState->clone() : nullptr;
        gameOver = other.gameOver;
    }
    return *this;
}

std::vector<int> turns; // TURNS FOR ISSUING PHASE

// ----------------------------------------------------------------
//                     Startup Phase
// ----------------------------------------------------------------

void GameEngine::startupPhase()
{
    const int MAX_GAMES = 5;
    const int MIN_GAMES = 1;
    const int MIN_MAXTURNS = 10;
    const int MAX_MAXTURNS = 50;
    const int MAX_PLAYERS = 4;
    numTurns = 0;
    this->playerCount = new int(0);
    std::vector<string> args;
    string input;
    while (true)
    {
        //cout << "\nEnter command:";
        input = commandProcessor->getCommand();
        args = commandProcessor->splitCommand(input);
        if (commandProcessor->validate(input))
        {
            if (args.at(0) == "tournament") {
                tournamentMode = true;

                //----------GETTING INFO FROM COMMAND--------
                int i = 1;

                //Collection of maps and players extracted from command
                vector<string> playerStrategies;

                //getting map files
                while (args.at(++i) != "-P") {
                    mapFiles.push_back(args.at(i));
                }

                int playerCounter = 0;
                //Getting player strategies, up to 4, add an Aggressuve player if less than 2.
                while (args.at(++i) != "-G") {
                    playerCounter++;
                    if(playerCounter<=MAX_PLAYERS){
                        playerStrategies.push_back(args.at(i));
                        cout<<playerCounter<<endl;
                    }
                }

                //Get number of games and max number of turns, check for base cases of minimum 1 game and maximum 5 games
                numGames = std::stoi(args.at(i+1));
                if(numGames>MAX_GAMES){
                    cout<<"The max games you set was too high, we set it to 5"<<endl;
                    numGames = MAX_GAMES;
                }
                else if(numGames<MIN_GAMES){
                    cout<<"The min games you set was too low, we set it to 1"<<endl;
                    numGames = MIN_GAMES;
                }
                maxTurns = std::stoi(args.at(i+3));
                if(maxTurns<MIN_MAXTURNS){
                    cout<<"The turns you set was too low, we set it to 10"<<endl;
                    maxTurns = MIN_MAXTURNS;
                }
                else if(maxTurns>MAX_MAXTURNS){
                    cout<<"The max turns you set was too high, we set it to 50"<<endl;
                    maxTurns = MAX_MAXTURNS;
                }

                cout<<"Max Number of Games: "<<numGames<<endl;
                cout<<"Max Number of Turns: "<<maxTurns<<endl;
                for(int i = 0;i < playerStrategies.size();i++){
                    cout<<"Player "<<(i+1)<<": "<<playerStrategies.at(i)<<endl;
                }

                system("pause");

                //--------------------------------------------

                //----------WRITING COMMANDS TO A FILE----------
                //Input File
                std::ofstream myfile;
                myfile.open("TournamentCommand.txt");

                //Each of the -G games have -M maps with -P players
                for (int map_i = 0; map_i < mapFiles.size(); map_i++) {
                    for (int game_i = 0; game_i < numGames; game_i++) {
                        myfile << "loadmap " << mapFiles.at(map_i) << "\n";
                        myfile << "validatemap" << "\n";
                        
                        //Addplayers
                        for (int player_i = 0; player_i < playerStrategies.size(); player_i++) {
                            string strategy = playerStrategies.at(player_i);
                            //Player name based on strategy and order
                            string playerName = strategy[0] + std::to_string(player_i+1);
                            myfile << "addplayer " << playerName << " " << strategy << "\n";
                        }
                        myfile << "gamestart" << "\n";
                        //Check if last game
                        myfile << ((game_i == numGames - 1 && map_i == mapFiles.size()-1) ? "quit" : "replay") << "\n";
                    }
                }
                myfile.close();
                //----------------------------------------------


                //----------------Replacing Command Processor-------------------
                //CmdProc replaced to make sure commands are read from tournament file
                delete commandProcessor;
                commandProcessor = new FileCommandProcessorAdapter("TournamentCommand.txt");
                //--------------------------------------------------------------

                cout << "Starting Tournement\n";
                transition(new Start());

            }
            else if (args.at(0) == "loadmap")
            {
                string fileName;
                fileName = args.at(1);
                std::cout << "\n"
                          << fileName << "\n";
                if (gameMap.loadMap(fileName) == 0)
                {
                    transition(new MapLoaded());
                }
                else
                {
                    if (tournamentMode) {
                        exit(0);
                    }
                    transition(new Start());
                }
            }
            else if (args.at(0) == "validatemap")
            {
                if (gameMap.validate() == 0)
                {
                    cout << "Map is valid\n";
                    transition(new MapValidated());
                }
                else
                {
                    if (tournamentMode) {
                        exit(0);
                    }
                    cout << "Map is not valid\n";
                    transition(new Start());
                }
            }
            else if (args.at(0) == "addplayer")
            {
                string name;
                name = args.at(1);
                string strategy = (args.size() == 3) ? args.at(2) : "Human";

                Player *p = new Player(name, this->playerCount, strategy);
                playerList.push_back(p);

                *(this->playerCount) = *(this->playerCount)+1;
                transition(new PlayersAdded());
            }
            else if (args.at(0) == "gamestart")
            {
                gamestart();
                transition(new AssignReinforcement());
                break;
            }
        }
        else
        {
            cout << "INCORRECT COMMAND\n";
        }
    }
}

// ----------------------------------------------------------------
//                     GAME START
// ----------------------------------------------------------------

void GameEngine::gamestart()
{
    // Equal Distribution of Territories
    for (int i = 0; i < gameMap.graph.size(); i++)
    {
        playerList.at(i % playerList.size())->addTerritory(&gameMap.graph.at(i));
    }
    
    std::cout <<endl; //line break for clarity

    // Give every Player 50 inital troops and drawing 2 cards
    for (int j = 0; j < playerList.size(); j++)
    {
        playerList.at(j)->_reinforcementPool = new int(50);

        playerList.at(j)->setHand(new Hand());
        std::cout << "Drawing cards..." << endl;
        deck.draw(*playerList.at(j)->getHand());
        deck.draw(*playerList.at(j)->getHand());
        for (int i = 0; i < playerList.size(); i++)
        {
            playerList.at(j)->negotiation.push_back(false);
        }
        playerList.at(j)->_doneTurn=new bool(false);

        //info output for each Player
        //Player Name
        std::cout << "\n" 
                  << "Player "
                  << playerList.at(j)->getName()
                  << "\n------------------------\n";
        //Player's ID
        std::cout << "ID #: "
                  << playerList.at(j)->getID();
        //Player'a base Recinformcments
        std::cout << "\n"
                  << "Reinforcement Pool: "
                  << *playerList.at(j)->_reinforcementPool;
        std::cout << "\n";
        //Player's cards in hand
        playerList.at(j)->printHand();
        std::cout << "------------------------" << endl;
    }

    // Shuffle player order
    for (int k = 0; k < playerList.size(); k++)
    {
        turns.push_back(k);
    }

    std::random_device rd;
    std::mt19937 m(rd());

    std::shuffle(turns.begin(), turns.end(), m);
}

// ----------------------------------------------------------------
//                          Game Loop
// ----------------------------------------------------------------

void GameEngine::mainGameLoop()
{
    while (gameEngine.getCurrentState() != "Win")
    {
        numTurns++;
        reinforcementPhase();

        gameEngine.transition(new IssueOrders());

        for(int i=0;i<playerList.size();i++){
            *playerList.at(i)->_doneTurn=false;
        }

        issueOrdersPhase();

        gameEngine.transition(new ExecuteOrders());

        executeOrdersPhase();
        if (checkWinCon() == 1)
        {
            gameEngine.transition(new Win());
        }
        else
        {
            transition(new AssignReinforcement());
        }
    }
    std::cout<<"GameOver: \n";
    // transition(new Win());

    string input=commandProcessor->getCommand();
    if(commandProcessor->validate(input)){
        if(input=="replay"){
            gameMap.clear();
            for (Player* player : playerList) {
                delete player;  // Free the memory
            }
            playerList.clear();  // Clear the vector
            // gameOver = true;
            turns.clear();
            transition(new Start());
        }
        else if(input=="quit"){
            transition(new End());
            gameOver = true;
        }
    }
}

// ----------------------------------------------------------------
//                     Reinforcement Phase
// ----------------------------------------------------------------

void GameEngine::reinforcementPhase()
{
    checkWinCon();
    //lets player know reinforcement phase has started
    std::cout << "\nNew troops have arrived!" << endl;

    // Reset:
    // reset's all territories that have -2 as owner to previous owner and reduce the size by half, This needs to be done before reinforcements can begin.
    for(int j=0;j<gameMap.graph.size();j++){
        if(*gameMap.graph.at(j).owner<-1){
            *gameMap.graph.at(j).owner=((*gameMap.graph.at(j).owner)+2)*(-1);
            *gameMap.graph.at(j).army=*gameMap.graph.at(j).army/2;
        }
    }

    for (int i = 0; i < playerList.size(); i++)
    {
        int reinforcement=0;
        int continentOwn [gameMap.continentList.size()];
        // Reset:
        // reset's all players negotiation arrays so that everything is false.
        for (int j = 0; j < playerList.size(); j++)
        {
            playerList.at(i)->negotiation.at(j) = false;
        }
        
        for (int j = 0; j < gameMap.graph.size(); j++)
        {
            if (*gameMap.graph.at(j).owner == playerList.at(i)->getID())
            {
                reinforcement++;
                int index;
                for(int l=0;l<gameMap.continentList.size();l++){
                    if(gameMap.continentList.at(l).name==gameMap.graph.at(j).pContient->name){
                        index=l;
                    }
                }
                continentOwn[index]++;
            }
        }
        std::cout<<"Reinforcements for "<<playerList.at(i)->getName()<<": "<<reinforcement;//DEMO
        reinforcement = std::floor((double)reinforcement / 3.00);
        int bonus=0;
        for (int k = 0; k < gameMap.continentList.size(); k++)
        {
            if (continentOwn[k] == *gameMap.continentList.at(k).nbrTerritories)
            {   
                bonus = bonus + *gameMap.continentList.at(k).bonus;
            }
            continentOwn[k]=0;
        }
        reinforcement=reinforcement+bonus;
        std::cout<<"/3 + "<<bonus<<" continent bonus = "<<reinforcement<<"\n";//DEMO
        if (reinforcement < 3)
        {
            std::cout<<"\nReinforcements too low. Set to 3\n";//DEMO
            reinforcement = 3;
        }
        *playerList.at(i)->_reinforcementPool = *playerList.at(i)->_reinforcementPool + reinforcement;
    }

    std::cout << "\n"; //new line for clarity
}

// ----------------------------------------------------------------
//                     Issue Orders Phase
// ----------------------------------------------------------------

void GameEngine::issueOrdersPhase()
{
    bool allPlayersDone = false; // flag to check if all players are done issuing orders
    std::cout << "|| Starting Order Issueing Phase ||" << endl;

    while (!allPlayersDone)
    {
        // Iterate through players in the order specified by `turns`
        for (int i=0;i<turns.size();i++)
        {  
            /* //BUG TESTING CHECKS:
            std::cout << "Turn Order = "<<endl;
            for (int i = 0; i < turns.size(); i++){
                std::cout << turns.at(i) << " ";}

            std::cout << "\nPlayer List Order = "<<endl;
            for (int i = 0; i < playerList.size(); i++){
                std::cout << playerList.at(i)->getName() << " ";}*/
            
            //skips player's turn if theyre done :)
            if (*playerList.at(turns.at(i))->_doneTurn == true){
                std::cout << "\n\n" << playerList.at(i)->getName() 
                         << " is done issuing orders.\n" << endl;
            }

            //runs player's turn for giving out orders!
            else{
                displayPlayerInfo(turns.at(i));
                
                // Takes in a player's command

                playerList.at(turns.at(i))->issueOrder();
            }  
        }
        //NOTE: playerList != turns list
        //      since playerList != turns, gotta make sure to check specifically at whichever 
        //      turns ID we're at in the playerList

        allPlayersDone = true;

        for(int j=0; j<playerList.size(); j++){
            if(*playerList.at(j)->_doneTurn == false){
                    allPlayersDone = false; // since this player issued an order, not all players are done
            }
        }
    }
    gameEngine.transition(new ExecuteOrders());
}

// ----------------------------------------------------------------
//                     Execute Orders Phase
// ----------------------------------------------------------------

void GameEngine::executeOrdersPhase()
{
    /*
    *Step1: Set the current order of every players list to head->getNext()
    *Step2: Check if player has finished executing orders, if all orders are executed. Set a boolean to true and skip step 3.
    *Step3: Execute Order.
    *Step4: Set the currentorder to currentorder->getNext()
    *Step5: Repeat steps 2-4. If all orders are executed, Proceed to Step 6.
    *Step6: If all players have finished their orders. Proceed to empty the list instead. 
    */
   cout<<"ATTEMPTING TO EXECUTE ORDERS!!!"<<endl;
   bool* executedOrders = new bool[playerList.size()];
   bool notDone = true;
   for(int i=0;i<playerList.size();i++){
        executedOrders[i]=false;
   }
   for(int i=0;i<playerList.size();i++){
        playerList.at(i)->getOrdersList()->setCurrentOrder(playerList.at(i)->getOrdersList()->getHead()->getNext());
   }
   int counter = 1;
   while(notDone){
        for(int i=0;i<playerList.size();i++){
            //Check if the size of the orderlist is less than the counter, if it is executedOrders[i] is true, continue.
            if(playerList.at(turns.at(i))->getOrdersList()->getSize()<counter){
                executedOrders[i] = true;
                continue;
            }
            playerList.at(turns.at(i))->getOrdersList()->getCurrentOrder()->execute();
            playerList.at(turns.at(i))->getOrdersList()->setCurrentOrder(playerList.at(turns.at(i))->getOrdersList()->getCurrentOrder()->getNext());
            //Execute Order of player.
        }
        //Check if all players finished their orders. If they did, set notDone to false to break the while loop.
        for(int i=0;i<playerList.size();i++){
            if(!executedOrders[i]){
                break;
            }
            else if(i==playerList.size()-1){
                notDone = false;
            }
        }
        counter++;
   }
   /*REMOVING THE ORDERS FROM THE LIST
   *Step 1: Check if list is empty.
   *Step 2: If not, remove the first order
   *Step 3: If yes, end loop
   */
   for(int i=0;i<playerList.size();i++){
        while(true){
            if(playerList.at(turns.at(i))->getOrdersList()->isEmpty()){
                break;
            }
            else{
                playerList.at(turns.at(i))->getOrdersList()->remove(1);
            }
        }
   }
    /*cout<<"ATTEMPTING TO EXECUTE ORDERS!!!"<<endl;
    cout<<playerList.at(0)->getOrdersList();
    cout<<playerList.at(1)->getOrdersList();
    playerList.at(0)->getOrdersList()->setCurrentOrder(playerList.at(0)->getOrdersList()->getHead()->getNext());
    playerList.at(1)->getOrdersList()->setCurrentOrder(playerList.at(1)->getOrdersList()->getHead()->getNext());
    playerList.at(0)->getOrdersList()->getCurrentOrder()->execute();
    playerList.at(1)->getOrdersList()->getCurrentOrder()->execute();
    playerList.at(0)->getOrdersList()->remove(1);
    playerList.at(1)->getOrdersList()->remove(1);  */    
        
    
}

int GameEngine::checkWinCon()
{

    //Game Draw
    if (tournamentMode && numTurns > maxTurns) {
        winners.push_back("Draw");
        return 1;
    }

    int territoriesOwned[playerList.size()];
    for(int i=0;i<playerList.size();i++){
        territoriesOwned[i]=0;
    }
    int endCon = 1;
    int currentWinner = *gameMap.graph.at(0).owner;
    territoriesOwned[currentWinner]=territoriesOwned[currentWinner]+1;

    for (int i = 1; i < gameMap.graph.size(); i++)
    {
        if (endCon == 1 && (currentWinner != *gameMap.graph.at(i).owner))
        {
            endCon = 0;
        }
        territoriesOwned[*gameMap.graph.at(i).owner]++;
    }
    if (endCon == 1)
    {
        if (tournamentMode) {
            winners.push_back(playerList.at(currentWinner)->getName());
        }
        return 1; // Game is over a player owns everything
    }
    for (int j = 0; j < playerList.size(); j++)
    {
        if (territoriesOwned[j] == 0)
        {
            playerList.erase(playerList.begin() + j);
            for(int k=0;k<gameMap.graph.size();k++){
                if(*gameMap.graph.at(k).owner>j){
                    *gameMap.graph.at(k).owner=*gameMap.graph.at(k).owner-1;
                }
            }
            for(int k=0;k<playerList.size();k++){
                if(*playerList.at(k)->_id>j){
                    *playerList.at(k)->_id=*playerList.at(k)->_id-1;
                }
            }
            for (int k = 0; k < turns.size(); k++)
            {
                if (turns[k] == j)
                {
                    turns.erase(turns.begin() + k);
                }
            }
            for (int k = 0; k < turns.size(); k++){
                if(turns[k]>j){
                    turns[k]=turns[k]-1;
                }
            }
        }
    }
    return 0;
}

//Display's a players current info on their turn
void GameEngine::displayPlayerInfo(int id){
    std::cout <<"\nPlayer " << playerList.at(id)->getName() << "'s Turn: "
              << "\n=======================" << endl;

    std::cout << "ID #: "
              << playerList.at(id)->getID();

    std::cout <<"\nCurrent Reinforcement Pool: "
              << *playerList.at(id)->_reinforcementPool;
    //Cards in hand
    std::cout <<"\n";
    playerList.at(id)->printHand();
    
    //Displays every single territory a player can attack
    // --> display problem: not showing properly the player's territories to attack
    //std::vector<Territory*> v;
    //v=playerList.at(id)->toAttack();
    std::vector<Territory*> attackList = playerList.at(id)->toAttack(); //Refresh and display every single territory a player can attack

    std::cout << "\n--------------";
    std::cout << "\n| Can Attack |\n";
    std::cout << "--------------" << endl;
    for (Territory* territory : attackList) {
        std::cout << *territory << "\n";
    }

    //std::cout<<*v.at(0)<<"\n";
    //for (int i=0;i<v.size();i++){
       // std::cout<<*v.at(i)<<"\n";
    //}

    //Displays every single territory a player can defend
    //v=playerList.at(id)->toDefend();

    // refresh and display every single territory a player can defend -- fix
    std::vector<Territory*> defendList = playerList.at(id)->toDefend();
    std::cout << "\n--------------";
    std::cout << "\n| To Defend |\n";
    std::cout << "--------------" << endl;
    for (Territory* territory : defendList) {
        std::cout << *territory << "\n";
    }

    /*std::cout <<"\n--------------";
    std::cout <<"\n| To Defend |\n";
    std::cout <<"--------------" << endl;

    //std::cout<<*v.at(0)<<"\n";
    for (int i=0;i<v.size();i++){
        std::cout<<*v.at(i)<<"\n";
    }*/
}


std::string GameEngine::getResults() {
    size_t numMaps = mapFiles.size();

    std::ostringstream oss;

    oss << "\nTournament mode:" << "\n";
    oss << "M: ";
    for (int i = 0; i < numMaps; i++){oss << mapFiles[i] << ", ";}
    oss << "\n";
    oss << "P: ";
    for (int i = 0; i < playerList.size(); i++){ oss << playerList.at(i)->getName() << ", "; }
    oss << "\n";
    oss << "G: " << numGames << "\n";
    oss << "D: " << maxTurns << "\n\n";

    // Calculate column widths
    size_t mapColumnWidth = 12; // Minimum width for the map names
    for (const std::string& map : mapFiles) {
        mapColumnWidth = std::max(mapColumnWidth, map.size());
    }

    size_t gameColumnWidth = 8; // Minimum width for the game columns
    for (const std::string& player : winners) {
        gameColumnWidth = std::max(gameColumnWidth, player.size());
    }



    // Border drawing function
    auto getHorizontalBorder = [&](size_t totalColumns) {
        std::ostringstream border;
        border << "+";
        border << std::string(mapColumnWidth + 2, '-') << "+"; // Map column
        for (size_t i = 0; i < totalColumns; ++i) {
            border << std::string(gameColumnWidth + 2, '-') << "+";
        }
        border << "\n";
        return border.str();
    };

    // Append top border
    oss << getHorizontalBorder(numGames);

    // Append header row
    oss << "| " << std::setw(mapColumnWidth) << std::left << "Results:" << " |";
    for (size_t game = 1; game <= numGames; ++game) {
        oss << " " << std::setw(gameColumnWidth) << std::left << "Game " + std::to_string(game) << " |";
    }
    oss << "\n";

    // Append header bottom border
    oss << getHorizontalBorder(numGames);

    // Append map rows
    for (size_t i = 0; i < numMaps; ++i) {
        oss << "| " << std::setw(mapColumnWidth) << std::left << mapFiles[i] << " |";
        for (size_t j = 0; j < numGames; ++j) {
            oss << " " << std::setw(gameColumnWidth) << std::left << winners[i * numGames + j] << " |";
        }
        oss << "\n";

        // Append row border
        oss << getHorizontalBorder(numGames);
    }

    return oss.str();
}