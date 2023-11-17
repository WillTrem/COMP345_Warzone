// PART 2.
//
// Implement a group of C++ classes that implement a Warzone player.
// Written by William Tremblay, 40174212.

#pragma once

#include <string>
#include <algorithm>

#include "Cards.h"
#include "Map.h"
#include "Player.h"

using namespace std;


// General constants / tuning params.
int NUM_TO_ATTACK = 5; // The number of territories AI players will targer/priorize in their attacking phase.
int NUM_TO_DEFEND = 5; // The number of territories AI players will targer/priorize in their defending phase.


// Abstract strategy class
class PlayerStrategy
{
private:
    Player *p;

public:
    // Default constructor
    PlayerStrategy();

    // Parametrized constructors
    //...

    // Main methods.
    virtual vector<Territory *> toAttack();

    virtual vector<Territory *> toDefend();

    virtual void issueOrder(Order *order);
};


// Human Player Strategy.
// "Requires user interactions to make decisions, including deploy and advance orders, as well as playing any card."
class HumanPlayerStrategy : public PlayerStrategy
{
public:
    // Constructor(s)

    vector<Territory*> toAttack();

    vector<Territory*> toDefend();

    void issueOrder(Order* order);
};



// Utility methods and structs.

// TO DO: DELETE UNUSED.
// Used to sort a vector of territories by the number of troops present on them.
struct LessThan_TroopsPresent 
{
    inline bool operator() (const Territory& A, const Territory& B);
};

// Used to stort a vector of territories by the number of enemy territories surrounding them. 
struct LessTan_SurroundingEnemies 
{
    inline bool operator() (const Territory& A, const Territory& B);
};

// Used to sort a vector of territories by the numberof troops present on them, then the number of enemy territories surrounding them.
// More owned troops present, more surrounding enemies = 'stronger' territory for offense.
struct LessThan_TroopsPresent_SurroundingEnemies
{
    inline bool operator() (const Territory& A, const Territory& B);
};

// Used to sort a vector of territories by the number of adjacent enemy troops. 
// More adjacent enemy troops = weaker territory.
struct LessThan_AdjacentEnemyTroops
{
    inline bool operator() (const Territory& A, const Territory& B);
};

// Used to sort a vector of territories by the number of adjacent enemy troops, then the number of one's own units present on them.
// More adjacent enemy troops, fewer owned troops = weaker territory.
struct LessThan_AdjacentEnemyTroops_TroopsPresent
{
    inline bool operator() (const Territory& A, const Territory& B);
};