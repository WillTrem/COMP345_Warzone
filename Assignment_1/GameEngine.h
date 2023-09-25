#pragma once

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <functional>


// #include "Orders.h"
#include "Cards.h"
#include "Player.h"

/**
 * Represents the various states a game can be in at any point in time
*/
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

/**
 * A command consists of:
 * 1. The command string that needs to be provided as input to run it
 * 2. The function that gets called when the command is entered
 * 3. The next state to transition into after command is ran
*/
class Command
{
public:
    std::string *cmdName;
    void (*action)();
    GameState *nextState;

    //Constructor
    Command(std::string *cmdName,  void (*action)(), GameState *nextState);
};

class GameEngine
{
private:
    std::map<GameState, std::list<Command>> *stateTransitions;

public:
    GameState *currentState;
    // Constructors
    GameEngine(GameState *currentState, std::map<GameState, std::list<Command>> *stateTransitions);
    GameEngine(const GameEngine &gameEngine);

    void executeCommand(std::string command);

    // Operator overloads
    void operator=(GameState &newState);
	friend std::ostream& operator<<(std::ostream &os, const GameEngine& gameEngine);

};