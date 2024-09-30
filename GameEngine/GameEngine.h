

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class State {
public:
    void loadmap();
    void validatemap();
    void addplayer();
    void assigncountries();

    void issueorder();
    void endissueorders();

    void execorder();
    void endexecorders();

    void win();
    void play();
    void end();

};

class Start : public State {};

class MapLoaded: public State {};

class MapValidated: public State {};

class PlayersAdded: public State {};

class AssignReinforcement: public State {};

class IssueOrders: public State {};

class ExecuteOrders: public State {};

class Win: public State {};


class GameEngine {
private:
    State state;
public:
    GameEngine();
    State changeState(State state);
};

#endif //GAMEENGINE_H
