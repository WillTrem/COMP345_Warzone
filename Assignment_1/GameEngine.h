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
    GameState *nextState;
    std::function<void()> *action;

    Command(std::string _cmdName, std::function<void()> _action, GameState _nextState);
    ~Command();
};

class GameEngine
{
private:
    std::map<GameState, std::list<Command>> *stateTransitions;

    void start();
    void loadMap();
    void validateMap();
    void addPlayer();
    void assignCountries();
    void issueOrder();
    void endIssueOrders();
    void executeOrder();
    void endExecuteOrders();
    void win();
    void end();

public:
    GameState *currentState;
    GameEngine();
    ~GameEngine();
    void executeCommand(std::string command);
};