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
    gameOver = false;
    currentState = new Start();
}

GameEngine::GameEngine(GameEngine *gameEngine)
{
    addObserver(loggingObserver);
    gameOver = gameEngine->gameOver;
    currentState = gameEngine->currentState ? gameEngine->currentState->clone() : nullptr;
}

void GameEngine::setGameOver(bool b) { gameOver = b; }

void GameEngine::run()
{
    string command;
    
    cout << "Welcome to Warzone\n"
         << endl;
    // Run first state
    // currentState->enter(*this);
    startupPhase();

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
    return "GameEngine new state: " + getCurrentState();
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
    this->playerCount = new int(0);
    std::vector<string> args;
    string input;
    while (true)
    {
        cout << "\nEnter command:";
        input = commandProcessor->getCommand();
        args = commandProcessor->splitCommand(input);
        if (commandProcessor->validate(input))
        {
            if (args.at(0) == "loadmap")
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
                    cout << "Map is not valid\n";
                    transition(new Start());
                }
            }
            else if (args.at(0) == "addplayer")
            {
                string name;
                name = args.at(1);
                playerList.push_back(new Player(name, this->playerCount));
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
    std::cout<<"GameOver: ";
    string input=commandProcessor->getCommand();
    if(commandProcessor->validate(input)){
        if(input=="replay"){
            system("exit");
        }else if(input=="quit"){
            system("exit");
        }
    }
}

// ----------------------------------------------------------------
//                     Reinforcement Phase
// ----------------------------------------------------------------

void GameEngine::reinforcementPhase()
{
    //lets player know reinforcement phase has started
    std::cout << "\nNew troops have arrived!" << endl;

    for (int i = 0; i < playerList.size(); i++)
    {
        int reinforcement=0;
        int* continentOwn = new int[gameMap.continentList.size()];
        // Reset:
        // reset's all players negotiation arrays so that everything is false.
        for (int j = 0; j < playerList.size(); j++)
        {
            playerList.at(i)->negotiation.at(j) = false;
        }
        // Reset:
        // reset's all territories that have -2 as owner to previous owner, This needs to be done before reinforcements can begin.
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
            else if (*playerList.at(turns.at(i))->_doneTurn == false) {
                displayPlayerInfo(turns.at(i));
                
                // Takes in a player's command
                std::cout<<"\nEnter command:";
                string command;
                std::getline(cin, command);

                playerList.at(turns.at(i))->issueOrder(command, &turns.at(i));
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
            playerList.at(turns.at(i))->getOrdersList()->setCurrentOrder(playerList.at(i)->getOrdersList()->getCurrentOrder()->getNext());
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
    int territoriesOwned[playerList.size()];
    int endCon = 1;
    int currentWinner = *gameMap.graph.at(0).owner;
    territoriesOwned[currentWinner]++;

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
        return 1; // Game is over a player owns everything
    }
    for (int j = 0; j < playerList.size(); j++)
    {
        if (territoriesOwned[j] == 0)
        {
            playerList.erase(playerList.begin() + j);
            for (int k = 0; k < turns.size(); k++)
            {
                if (turns[k] == j)
                {
                    turns.erase(turns.begin() + k);
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
    std::vector<Territory*> v;
    v=playerList.at(id)->toAttack();

    std::cout <<"\n--------------";
    std::cout <<"\n| Can Attack |\n";
    std::cout <<"--------------" << endl;

    //std::cout<<*v.at(0)<<"\n";
    for (int i=0;i<v.size();i++){
        std::cout<<*v.at(i)<<"\n";
    }

    //Displays every single territory a player can defend
    v=playerList.at(id)->toDefend();

    std::cout <<"\n--------------";
    std::cout <<"\n| To Defend |\n";
    std::cout <<"--------------" << endl;

    //std::cout<<*v.at(0)<<"\n";
    for (int i=0;i<v.size();i++){
        std::cout<<*v.at(i)<<"\n";
    }
}