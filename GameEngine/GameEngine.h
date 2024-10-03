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

};

class Start: public State {
    State* handleInput(GameEngine& game_engine,  std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;
};
class MapLoaded: public State {
    State* handleInput(GameEngine& game_engine,  std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;
};
class MapValidated: public State {
    State* handleInput(GameEngine& game_engine,  std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;
};
class PlayersAdded: public State {
    State* handleInput(GameEngine& game_engine,  std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;
};
class AssignReinforcement: public State {
    State* handleInput(GameEngine& game_engine,  std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;
};
class IssueOrders: public State {
    State* handleInput(GameEngine& game_engine,  std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;
};
class ExecuteOrders: public State {
    State* handleInput(GameEngine& game_engine,  std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;
};
class Win: public State {
    State* handleInput(GameEngine& game_engine,  std::string& input) override;
    void enter(GameEngine& game_engine) override;
    void exit(GameEngine& game_engine) override;
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
