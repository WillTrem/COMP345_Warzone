// PART 2.
//
// Implement a group of C++ classes that implement a Warzone player.
// Written by William Tremblay, 40174212.

#pragma once

#include <string>

#include "Cards.h"
// #include "Map.h"
#include "Player.h"

using namespace std;

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

    virtual vector<Territory *> toAttack();

    virtual vector<Territory *> toDefend();

    virtual void issueOrder(Order *order);
};
