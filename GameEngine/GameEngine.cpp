//
// Created by minha on 10/2/2024.
//

#include "GameEngine.h"
#include <iostream>
#include "../Map/Map.h"

using namespace std;



State::State(){}
State::State(State& state){}
State& State::operator=(const State& other) {
    return *this;
}

//--------------------START STATE--------------------


State* Start::clone(){
    return new Start();
}

//handle input takes in the input command and game_engine that the state may use to change game behavior
State* Start::handleInput(GameEngine& game_engine, std::string& input){
    if (input=="loadmap"){
        string fileName;
        cin>>fileName;
        std::cout<<"\n"<<fileName<<"\n";
        if(map.loadMap(fileName)==0){
            return new MapLoaded();
        }else{
            return new Start();
        }
    }
    return nullptr;
}

//run when a state reaction is finalized
void Start::enter(GameEngine& game_engine) {
    cout << "Entering Start State\n" << endl;
    cout << "Commands: loadmap\n\n";

}
//run before a state is deleted
void Start::exit(GameEngine& game_engine) {
    cout << "\nExiting Start State" << endl;
}

//--------------------MAP LOADER STATE--------------------

State* MapLoaded::clone(){
    return new MapLoaded();
}

State* MapLoaded::handleInput(GameEngine& game_engine, std::string& input){
    if (input=="loadmap"){
        string fileName;
        cin>>fileName;
        std::cout<<"\n"<<fileName<<"\n";
        if(map.loadMap(fileName)==0){
            return new MapLoaded();
        }else{
            return new Start();
        }
    }
    if (input == "validatemap") {
        if(map.validate()==0){
            return new MapValidated();
        }else{
            return new Start();
        }
    }
    return nullptr;
}

void MapLoaded::enter(GameEngine& game_engine) {
    cout << "Entering MapLoaded State\n" << endl;
    cout << "Commands: loadmap, validatemap\n\n";
}

void MapLoaded::exit(GameEngine& game_engine) {
    cout << "\nExiting MapLoaded State" << endl;
}


//--------------------MAP VALIDATED STATE--------------------

State* MapValidated::clone(){
    return new MapValidated();
}

State* MapValidated::handleInput(GameEngine& game_engine, std::string& input) {
    if (input == "addplayer") {
        return new PlayersAdded();
    }
    return nullptr;
}

void MapValidated::enter(GameEngine& game_engine) {
    cout << "Entering MapValidated State\n" << endl;
    cout << "Commands: addplayer\n\n";
}

void MapValidated::exit(GameEngine& game_engine) {
    cout << "\nExiting MapValidated State" << endl;
}


//--------------------PLAYERS ADDED STATE--------------------

State* PlayersAdded::clone(){
    return new PlayersAdded();
}

State* PlayersAdded::handleInput(GameEngine& game_engine, std::string& input) {
    if (input == "addplayer") {
        return new PlayersAdded();
    }

    if (input == "assigncountries") {
        return new AssignReinforcement();
    }
    return nullptr;
}

void PlayersAdded::enter(GameEngine& game_engine) {
    cout << "Entering PlayersAdded State\n" << endl;
    cout << "Commands: addplayer, assigncountries\n\n";
}

void PlayersAdded::exit(GameEngine& game_engine) {
    cout << "\nExiting PlayersAdded State" << endl;
}


//--------------------ASSIGN REINFORCEMENT STATE--------------------

State* AssignReinforcement::clone(){
    return new AssignReinforcement();
}

State* AssignReinforcement::handleInput(GameEngine& game_engine, std::string& input) {
    if (input == "issueorder") {
        return new IssueOrders();
    }
    return nullptr;
}

void AssignReinforcement::enter(GameEngine& game_engine) {
    cout << "Entering AssignReinforcement State\n" << endl;
    cout << "Commands: issueorder\n\n";
}

void AssignReinforcement::exit(GameEngine& game_engine) {
    cout << "\nExiting AssignReinforcement State" << endl;
}

//--------------------ISSUE ORDERS STATE--------------------
State* IssueOrders::clone(){
    return new IssueOrders();
}

State* IssueOrders::handleInput(GameEngine& game_engine, std::string& input) {
    if (input == "issueorder") {
        return new IssueOrders();
    }
    if (input == "endissueorders") {
        return new ExecuteOrders();
    }
    return nullptr;
}

void IssueOrders::enter(GameEngine& game_engine) {
    cout << "Entering IssueOrders State\n" << endl;
    cout << "Commands: issueorder, endissueorders\n\n";
}

void IssueOrders::exit(GameEngine& game_engine) {
    cout << "\nExiting IssueOrders State" << endl;
}

//--------------------EXECUTE ORDERS STATE--------------------
State* ExecuteOrders::clone(){
    return new ExecuteOrders();
}

State* ExecuteOrders::handleInput(GameEngine& game_engine, std::string& input) {
    if (input == "execorder") {
        return new ExecuteOrders();
    }
    if (input == "endexecorders") {
        return new AssignReinforcement();
    }

    if (input == "win") {
        return new Win();
    }
    return nullptr;
}

void ExecuteOrders::enter(GameEngine& game_engine) {
    cout << "Entering ExecuteOrders State\n" << endl;
    cout << "Commands: execorder, endexecorders, win\n\n";
}

void ExecuteOrders::exit(GameEngine& game_engine) {
    cout << "\nExiting ExecuteOrders State" << endl;
}

//--------------------WIN STATE--------------------
State* Win::clone(){
    return new Win();
}

State* Win::handleInput(GameEngine& game_engine, std::string& input) {
    if (input == "end") {
        game_engine.setGameOver(true);
        return new End();

    }
    if (input == "play") {
        return new Start();
    }
    return nullptr;
}

void Win::enter(GameEngine& game_engine) {
    cout << "Entering Win State\n" << endl;
    cout << "Commands: end, play\n\n";
}

void Win::exit(GameEngine& game_engine) {
    cout << "\nExiting Win State" << endl;
}

//--------------------END STATE--------------------
State* End::clone(){
    return new End();
}

State* End::handleInput(GameEngine& game_engine, std::string& input) {
    return nullptr;
}

void End::enter(GameEngine& game_engine) {
    cout << "Entering End State\n" << endl;
//    cout << "Commands: end, play\n\n";
}

void End::exit(GameEngine& game_engine) {
    cout << "\nExiting End State" << endl;
}




std::ostream& operator<<(std::ostream& os, const State& state) {
    os << "Current State: " << state.getName();
    return os;
}

//##############################################################################//

//--------------------GAME ENGINE--------------------
GameEngine::GameEngine() {
    gameOver = false;
    currentState = new Start();
}

GameEngine::GameEngine(GameEngine* gameEngine){
    gameOver = gameEngine->gameOver;
    currentState = gameEngine->currentState ? gameEngine->currentState->clone() : nullptr;
}

void GameEngine::setGameOver(bool b){ gameOver = b; }

void GameEngine::run() {
    string command;
    cout << "Welcome to Warzone\n" << endl;
    //Run first state
    currentState->enter(*this);

    while (true) {
        cout << "Enter command:";
        cin >> command;
        handleInput(command);

        if (gameOver) {
            cout << "Game has ended!" << endl;
            break;
        }
    }

}

void GameEngine::handleInput(std::string& input) {
    State* nextState = currentState->handleInput(*this,  input);

    if (nextState != nullptr) {
        currentState->exit(*this);

        delete currentState;
        currentState = nextState;

        currentState->enter(*this);
    }
    else {
        cout << "INCORRECT COMMAND\n" << endl;
    }

}

std::ostream& operator<<(std::ostream& os, const GameEngine& engine) {
    os << *engine.currentState << ".\nIs the game over: " << (engine.gameOver == true? "YES" : "NO") ;
    return os;
}

GameEngine& GameEngine::operator=(const GameEngine& other) {
    if (this != &other) {

        delete currentState;
        currentState = other.currentState ? other.currentState->clone() : nullptr;
        gameOver = other.gameOver;
    }
    return *this;
}

void GameEngine::startupPhase(){
    
}
