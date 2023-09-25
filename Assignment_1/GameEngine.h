#pragma once

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <functional>


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
    std::string *cmdName;
    std::function<void()> *action;
    GameState *nextState;

    Command(std::string *cmdName, std::function<void()> *action, GameState *nextState);
};

class GameEngine
{
private:
    std::map<GameState, std::list<Command>> *stateTransitions;

public:
    GameState *currentState;

    GameEngine(GameState *currentState, std::map<GameState, std::list<Command>> *stateTransitions);

    void executeCommand(std::string command);
};