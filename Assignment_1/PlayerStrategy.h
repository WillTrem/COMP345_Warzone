#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <set>

#include "Cards.h"
#include "Map.h"
#include "Player.h"
#include "Orders.h"

using namespace std;

// General constants / tuning params.
extern const int NUM_TO_ATTACK; // The number of territories AI players will targer/priorize in their attacking phase.
extern const int NUM_TO_DEFEND; // The number of territories AI players will targer/priorize in their defending phase.

#ifndef PLAYER_STRATEGY_H
#define PLAYER_STRATEGY_H
class Player;
// Abstract strategy class
class PlayerStrategy
{
protected: // So that it remain accessible by child classes.
    Player *p;

public:
    // Default constructor
    PlayerStrategy();

    // Parametrized constructors
    //...

    // Main methods.
    virtual vector<Territory *> toAttack() = 0;

    virtual vector<Territory *> toDefend() = 0;

    virtual void issueOrder(Order *order) = 0;

    // Utility methods.
    vector<Territory *> getAdjacentTerritories(); // Returns a vector of all enemy territories adjacent to the player's.
};

// Human Player Strategy.
// "Requires user interactions to make decisions, including deploy and advance orders, as well as playing any card."
class HumanPlayerStrategy : public PlayerStrategy
{
public:
    // Constructor(s)
    HumanPlayerStrategy();

    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder(Order *order);
};

// Aggressive Player Strategy.
// "Computer player that focuses on attack (deploys or advances armies on its strongest country, then always advances to enemy territories until it cannot do so anymore; will use any card with an aggressive purpose.)"
class AggressivePlayerStrategy : public PlayerStrategy
{
public:
    // Constructor(s)
    AggressivePlayerStrategy();

    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder(Order *order);
};

// Benevolent Player Strategy.
// "Computer player that focuses on protecting its weak countries (deploys or advances armies on its weakest countries, never advances to enemy territories; may use cards but will never use a card in a way that purposefully will harm anyone)."
class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
    // Constructor(s)
    BenevolentPlayerStrategy();

    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder(Order *order);
};

// Neutral Player Strategy.
// "Computer player that never issues any order, nor uses any cards, though it may have or receive cards.If a Neutral player is attacked, it becomes an Aggressive player."
class NeutralPlayerStrategy : public PlayerStrategy
{
public:
    // Constructor(s)
    NeutralPlayerStrategy();

    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder(Order *order);
};

// Cheater Player Strategy.
// "Computer player that automatically conquers all territories that are adjacent to its own territories(only once per turn). Does not use cards, though it may have or receive cards."
class CheaterPlayerStrategy : public PlayerStrategy
{
public:
    // Constructor(s)
    CheaterPlayerStrategy();

    vector<Territory *> toAttack();

    vector<Territory *> toDefend();

    void issueOrder(Order *order);
};

// Utility structs.

// TO DO: DELETE UNUSED.

// Used to sort a vector of territories by the number of troops present on them.
// Used by the Aggressive player's toAttack() method.
struct LessThan_TroopsPresent
{
    inline bool operator()(const Territory *A, const Territory *B);
};

// Used to stort a vector of territories by the number of enemy territories surrounding them.
struct LessTan_SurroundingEnemies
{
    inline bool operator()(const Territory *A, const Territory *B);
};

// Used to sort a vector of territories by the numberof troops present on them, then the number of enemy territories surrounding them.
// More owned troops present, more surrounding enemies = 'stronger' territory for offense.
struct LessThan_TroopsPresent_SurroundingEnemies
{
    inline bool operator()(const Territory *A, const Territory *B);
};

// Used to sort a vector of territories by the number of adjacent enemy troops.
// More adjacent enemy troops = weaker territory.
struct LessThan_AdjacentEnemyTroops
{
    inline bool operator()(const Territory *A, const Territory *B);
};

// Used to sort a vector of territories by the number of adjacent enemy troops, then the number of one's own units present on them.
// More adjacent enemy troops, fewer owned troops = weaker territory.
// Used by the Benevolent Player's toDefend() method.
struct LessThan_AdjacentEnemyTroops_TroopsPresent
{
    inline bool operator()(const Territory *A, const Territory *B);
};

#endif