//
// Created by minha on 11/11/2024.
//

#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H
#include "../Player/Player.h"


class PlayerStrategies {
    protected:
    Player*player = nullptr;
    public:
    explicit PlayerStrategies(Player* player) : player(player) {}
    virtual ~PlayerStrategies() = default;
    virtual void issueOrder(){};
    virtual std::vector<Territory*> toAttack(){std::vector<Territory*> a;return a;}
    virtual std::vector<Territory*> toDefend(){std::vector<Territory*> a;return a;};
};

/*
requires user interactions to make decisions,
including deploy and advance orders,
as well as playing any card.
 */
class HumanPlayerStrategy : public PlayerStrategies {
public:
 explicit HumanPlayerStrategy(::Player *player): PlayerStrategies(player){}
 ~HumanPlayerStrategy() override;
 void issueOrder() override;
 std::vector<Territory*> toAttack() override;
 std::vector<Territory*> toDefend() override;
};

/*
computer player that focuses on attack (deploys or advances armies on its strongest country,
then always advances to enemy territories until it cannot do so anymore;
will use any card with an aggressive purpose, as defined above).
 */
class AggressivePlayerStrategy : public PlayerStrategies {
public:
 explicit AggressivePlayerStrategy(::Player *player) : PlayerStrategies(player){}
 //~AggressivePlayerStrategy() override;
 void issueOrder() override;
 std::vector<Territory*> toAttack() override;
 std::vector<Territory*> toDefend() override;
};

/*
computer player that focuses on protecting its weak countries (deploys or advances armieson its weakest countries,
never advances to enemy territories;
may use cards but will never use a card in a way that purposefully will harm anyone).
 */
class BenevolentPlayerStrategy : public PlayerStrategies {
public:
 explicit BenevolentPlayerStrategy(::Player *player): PlayerStrategies(player) {}
 //~BenevolentPlayerStrategy() override;
 void issueOrder() override;
 std::vector<Territory*> toAttack() override;
 std::vector<Territory*> toDefend() override;
};

/*
computer player that never issues any order, nor uses any cards, though it may have or receive cards.
If a Neutral player is attacked, it becomes an Aggressive player.
 */
class NeutralPlayerStrategy : public PlayerStrategies {
public:
 explicit NeutralPlayerStrategy(::Player *player): PlayerStrategies(player) {}
 ~NeutralPlayerStrategy() override;
 void issueOrder() override;
 std::vector<Territory*> toAttack() override;
 std::vector<Territory*> toDefend() override;
};

/*
Cheater player: computer player that automatically conquers all territories that are adjacent to its own
territories (only once per turn). Does not use cards, though it may have or receive cards.
 */
class CheaterPlayerStrategy : public PlayerStrategies {
public:
 explicit CheaterPlayerStrategy(::Player *player): PlayerStrategies(player) {}
 ~CheaterPlayerStrategy() override;
 void issueOrder() override;
 std::vector<Territory*> toAttack() override;
 std::vector<Territory*> toDefend() override;
};



#endif //PLAYERSTRATEGIES_H
