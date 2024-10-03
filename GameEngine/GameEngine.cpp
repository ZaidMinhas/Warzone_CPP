//
// Created by minha on 10/2/2024.
//

#include "GameEngine.h"
#include <iostream>

using namespace std;

std::ostream& operator<<(std::ostream& os, const State& state) {
    os << "Current State: " << state.getName();
    return os;
}

//--------------------START STATE--------------------

//handle input takes in the input command and game_engine that the state may use to change game behavior
State* Start::handleInput(GameEngine& game_engine, std::string& input){
    if (input == "loadmap"){
        return new MapLoaded();
    }
    return nullptr;
}

//run when a state reaction is finalized
void Start::enter(GameEngine& game_engine) {
    cout << "Entering Start State\n" << endl;
}
//run before a state is deleted
void Start::exit(GameEngine& game_engine) {
    cout << "\nExiting Start State" << endl;
}

//--------------------MAP LOADER STATE--------------------
State* MapLoaded::handleInput(GameEngine& game_engine, std::string& input){
    if (input == "loadmap"){
        return new MapLoaded();
    }
    if (input == "validatemap") {
        return new MapValidated();
    }
    return nullptr;
}

void MapLoaded::enter(GameEngine& game_engine) {
    cout << "Entering MapLoaded State\n" << endl;
}

void MapLoaded::exit(GameEngine& game_engine) {
    cout << "\nExiting MapLoaded State" << endl;
}


//--------------------MAP VALIDATED STATE--------------------
State* MapValidated::handleInput(GameEngine& game_engine, std::string& input) {
    if (input == "addplayer") {
        return new PlayersAdded();
    }
    return nullptr;
}

void MapValidated::enter(GameEngine& game_engine) {
    cout << "Entering MapValidated State\n" << endl;
}

void MapValidated::exit(GameEngine& game_engine) {
    cout << "\nExiting MapValidated State" << endl;
}


//--------------------PLAYERS ADDED STATE--------------------
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
}

void PlayersAdded::exit(GameEngine& game_engine) {
    cout << "\nExiting PlayersAdded State" << endl;
}


//--------------------ASSIGN REINFORCEMENT STATE--------------------
State* AssignReinforcement::handleInput(GameEngine& game_engine, std::string& input) {
    if (input == "issueorder") {
        return new IssueOrders();
    }
    return nullptr;
}

void AssignReinforcement::enter(GameEngine& game_engine) {
    cout << "Entering AssignReinforcement State\n" << endl;
}

void AssignReinforcement::exit(GameEngine& game_engine) {
    cout << "\nExiting AssignReinforcement State" << endl;
}

//--------------------ISSUE ORDERS STATE--------------------
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
}

void IssueOrders::exit(GameEngine& game_engine) {
    cout << "\nExiting IssueOrders State" << endl;
}

//--------------------EXECUTE ORDERS STATE--------------------
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
}

void ExecuteOrders::exit(GameEngine& game_engine) {
    cout << "\nExiting ExecuteOrders State" << endl;
}

//--------------------WIN STATE--------------------
State* Win::handleInput(GameEngine& game_engine, std::string& input) {
    if (input == "end") {
        game_engine.setGameOver(true);
    }
    if (input == "play") {
        return new Start();
    }
    return nullptr;
}

void Win::enter(GameEngine& game_engine) {
    cout << "Entering Win State\n" << endl;
}

void Win::exit(GameEngine& game_engine) {
    cout << "\nExiting Win State" << endl;
}

//##############################################################################//

//--------------------GAME ENGINE--------------------
GameEngine::GameEngine() {
    gameOver = false;
    currentState = new Start();
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


