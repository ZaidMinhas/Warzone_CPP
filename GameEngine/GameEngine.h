//
// Created by minha on 10/2/2024.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <string>


class GameEngine;

class State {

    public:
    virtual ~State() = default;


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
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Start State";
    }
};

class MapLoaded : public State {
public:
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Map Loaded State";
    }
};

class MapValidated : public State {
public:
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Map Validated State";
    }
};

class PlayersAdded : public State {
public:
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Players Added State";
    }
};

class AssignReinforcement : public State {
public:
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Assign Reinforcement State";
    }
};

class IssueOrders : public State {
public:
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Issue Orders State";
    }
};

class ExecuteOrders : public State {
public:
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Execute Orders State";
    }
};

class Win : public State {
public:
    State* handleInput(GameEngine& game_engine, std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;

    std::string getName() const override {
        return "Win State";
    }
};






class GameEngine {
    public:
    GameEngine();

    void run();
    void handleInput(std::string& input);

    void setGameOver(bool b);

private:
    State* currentState;
    bool gameOver;
};

#endif //GAMEENGINE_H
