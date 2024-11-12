//
// Created by minha on 11/11/2024.
//

#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

class PlayerStrategies {
    public:
    virtual void issueOrder();
    virtual void toAttack();
    virtual void toDefend();
};

/*
requires user interactions to make decisions,
including deploy and advance orders,
as well as playing any card.
 */
class HumanPlayerStrategy : public PlayerStrategies {};

/*
computer player that focuses on attack (deploys or advances armies on its strongest country,
then always advances to enemy territories until it cannot do so anymore;
will use any card with an aggressive purpose, as defined above).
 */
class AggressivePlayerStrategy : public PlayerStrategies {};

/*
computer player that focuses on protecting its weak countries (deploys or advances armieson its weakest countries,
never advances to enemy territories;
may use cards but will never use a card in a way that purposefully will harm anyone).
 */
class BenevolentPlayerStrategy : public PlayerStrategies {};

/*
computer player that never issues any order, nor uses any cards, though it may have or receive cards.
If a Neutral player is attacked, it becomes an Aggressive player.
 */
class NeutralPlayerStrategy : public PlayerStrategies {};

/*
Cheater player: computer player that automatically conquers all territories that are adjacent to its own
territories (only once per turn). Does not use cards, though it may have or receive cards.
 */

#endif //PLAYERSTRATEGIES_H
