//
// Created by minha on 10/2/2024.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using std::string, std::vector;

class GameEngine;

class State {

    public:
    State();
    State(State& state);

    virtual ~State() = default;
    State& operator=(const State& other);

    virtual State* clone()  = 0;


    virtual State* handleInput(GameEngine& game_engine, std::string& input) = 0;

    virtual void enter(GameEngine& game_engine) = 0;
    virtual void exit(GameEngine& game_engine) = 0;
    // virtual void update(GameEngine& game_engine) = 0;

    virtual std::string getName() const = 0;

    // Declare the insertion operator as a friend function

    friend std::ostream& operator<<(std::ostream& os, const State& state);

};

class Start : public State {
public:

    State* clone()  override;
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Start";
    }
};

class MapLoaded : public State {
public:
    State* clone()  override;
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Map Loaded";
    }
};

class MapValidated : public State {
public:
    State* clone()  override;
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Map Validated";
    }
};

class PlayersAdded : public State {
public:
    State* clone()  override;
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Players Added";
    }
};

class AssignReinforcement : public State {
public:
    State* clone()  override;
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Assign Reinforcement";
    }
};

class IssueOrders : public State {
public:
    State* clone()  override;
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Issue Orders";
    }
};

class ExecuteOrders : public State {
public:
    State* clone()  override;
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Execute Orders";
    }
};

class Win : public State {
public:
    State* clone() override;
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Win";
    }
};

class End : public State {
public:
    State* clone() override;
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "End";
    }
};




class GameEngine {
    public:
    GameEngine();
    GameEngine(GameEngine* game_engine);
    GameEngine& operator=(const GameEngine& other);

    void run();
    void handleInput(std::string& input);

    void setGameOver(bool b);

    friend std::ostream& operator<<(std::ostream& os, const GameEngine& engine);

    void startupPhase();
    void gamestart();
    int checkWinCon();
    void setCurrentState(State* state);
    std::string getCurrentState();
    
private:
    int* playerCount;
    State* currentState;
    bool gameOver;
};

extern GameEngine gameEngine;
extern std::vector<int> turns;


#endif //GAMEENGINE_H
