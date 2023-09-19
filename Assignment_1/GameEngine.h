#pragma once

#include <map>
#include <list>
#include "Orders.h"
#include "Cards.h"
#include "Player.h"

enum GameState
{
    // Start states
    START,
    MAP_LOADED,
    MAP_VALIDATED,
    PLAYERS_ADDED,
    // Play states
    ASSIGN_REINFORCEMENTS,
    ISSUE_ORDERS,
    EXECUTE_ORDERS,
    WIN,
    END
};

struct GameStateAction
{
public:
    GameState nextState;
    void (*action)();

    GameStateAction(void (*a)(), GameState ns );
};

class GameEngine
{
private:
    std::map<GameState, std::list<GameStateAction>> stateTransitions;
    GameState currentState;

public:
    GameEngine();
    void transitionToNextState();
};