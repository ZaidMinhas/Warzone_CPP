//
// Created by minha on 11/11/2024.
//

#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H
#include "..\Player/Player.h"


class PlayerStrategies {
    Player*player = nullptr;
    public:
    explicit PlayerStrategies(Player* player) : player(player) {}
    virtual ~PlayerStrategies() = default;
    virtual void issueOrder();
    virtual void toAttack();
    virtual void toDefend();
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
 void toAttack() override;
 void toDefend() override;
};

/*
computer player that focuses on attack (deploys or advances armies on its strongest country,
then always advances to enemy territories until it cannot do so anymore;
will use any card with an aggressive purpose, as defined above).
 */
class AggressivePlayerStrategy : public PlayerStrategies {
public:
 explicit AggressivePlayerStrategy(::Player *player) : PlayerStrategies(player){}
 ~AggressivePlayerStrategy() override;
 void issueOrder() override;
 void toAttack() override;
 void toDefend() override;
};

/*
computer player that focuses on protecting its weak countries (deploys or advances armieson its weakest countries,
never advances to enemy territories;
may use cards but will never use a card in a way that purposefully will harm anyone).
 */
class BenevolentPlayerStrategy : public PlayerStrategies {
public:
 explicit BenevolentPlayerStrategy(::Player *player): PlayerStrategies(player) {}
 ~BenevolentPlayerStrategy() override;
 void issueOrder() override;
 void toAttack() override;
 void toDefend() override;
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
 void toAttack() override;
 void toDefend() override;
};

/*
Cheater player: computer player that automatically conquers all territories that are adjacent to its own
territories (only once per turn). Does not use cards, though it may have or receive cards.
 */

#endif //PLAYERSTRATEGIES_H
