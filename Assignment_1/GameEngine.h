#pragma once

#include <map>
#include <list>
#include <string>
#include <iostream>
// #include "Orders.h"
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

class Command
{
public:
    std::string cmdName;
    GameState nextState;
    void (*action)();
    Command(std::string _cmdName, void (*_action)(), GameState _nextState);
};

class GameEngine
{
private:
    std::map<GameState, std::list<Command>> stateTransitions;

public:
    GameState currentState;
    GameEngine();
    void executeCommand(std::string command);
};