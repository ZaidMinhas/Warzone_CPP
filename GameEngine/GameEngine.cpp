//
// Created by minha on 10/2/2024.
//

#include "GameEngine.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
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
        game_engine.gamestart();
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
    this->playerCount = new int(0);
    cout << "Welcome to Warzone\n"
         << endl;
    // Run first state
    //currentState->enter(*this);
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

///////////////////////////////////////////////////////
//                   Startup Phase                   //
///////////////////////////////////////////////////////

std::vector<int> turns;

void GameEngine::startupPhase()
{
    std::vector<string> args;
    string input;
    while (true)
    {
        cout << "Enter command:";
        input = commandProcessor.getCommand();
        args = commandProcessor.splitCommand(input);
        if (commandProcessor.validate(input))
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
                this->playerCount++;
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

void GameEngine::gamestart()
{
    // Equal Distribution of Territories
    for (int i = 0; i < gameMap.graph.size(); i++)
    {
        playerList.at(i % playerList.size())->addTerritory(&gameMap.graph.at(i));
    }
    // Determin random order of play

    // Give every Player 50 inital troops and drawing 2 cards
    for (int j = 0; j < playerList.size(); j++)
    {
        playerList.at(j)->_reinforcementPool = new int(50);
        playerList.at(j)->_handCard = new Hand();
        deck.draw(*playerList.at(j)->_handCard);
        deck.draw(*playerList.at(j)->_handCard);
        std::cout << "\n"
                  << playerList.at(j)->getName();
        std::cout << "\n"
                  << *playerList.at(j)->_reinforcementPool;
        std::cout << "\n"
                  << *playerList.at(j)->_handCard;
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