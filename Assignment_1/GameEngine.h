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
using namespace std;
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
    std::string cmdName;
    std::string parameter;
    void (*action)();
    GameState *nextState;
    string effect;

    //Constructor
    Command(std::string cmdName);
    Command(std::string cmdName, std::string parameter);
    Command(std::string *cmdName,  void (*action)(), GameState *nextState);
    Command(const Command &command);
    
    // Saves the effect of the command after execution
    void saveEffect(string effect);

};

class GameEngine
{
private:
    std::map<GameState, std::list<Command>> *stateTransitions;

public:
    GameState *currentState;
    //CommandProcessor* commandProcessor;


    // Constructors
    GameEngine();
    GameEngine(GameState *currentState, std::map<GameState, std::list<Command>> *stateTransitions);
    GameEngine(const GameEngine &gameEngine);

    void executeCommand(std::string command);

    void startupPhase();

    // Operator overloads
    void operator=(GameState &newState);
	friend std::ostream& operator<<(std::ostream &os, const GameEngine& gameEngine);

};