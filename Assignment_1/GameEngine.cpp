#include "GameEngine.h"

// Constructor with only command name
Command::Command(std::string cmdName) : cmdName(cmdName) {}

//Constructor with with both command name and parameter
Command::Command(std::string cmdName, std::string parameter) : cmdName(cmdName), parameter(parameter) {}


/**
 * Normal constructor
*/
Command::Command(std::string *cmdName, void (*action)(), GameState *nextState):
    cmdName(*cmdName),
    action(action),
    nextState(nextState) {}

/**
 * Copy constructor
*/
Command::Command(const Command &command) : 
    cmdName(command.cmdName),
    action(command.action),
    nextState(command.nextState) {}

// Default constuctor for GameEngine
GameEngine::GameEngine(){
    GameState startState = START;
    currentState = &startState;
    stateTransitions = nullptr;
}

/**
 * Normal constructor
*/
GameEngine::GameEngine(GameState* currentState, std::map<GameState, std::list<Command>>* stateTransitions):
    currentState(currentState), 
    stateTransitions(stateTransitions) {}

/**
 * Copy constructor
*/
GameEngine::GameEngine(const GameEngine &gameEngine): 
    currentState(gameEngine.currentState), 
    stateTransitions(gameEngine.stateTransitions) {}

/**
 * 1. Checks to see if the commmand is a valid command at the current state
 * 2. executes the transistion function (action)
 * 3. Make currentState point to the new state
*/
void GameEngine::executeCommand(std::string commandArg)
{
    bool cmdSucessful = false;

    // passed by reference instead of value so no new variables are created
    for (auto &cmd : (*stateTransitions)[*currentState])
    {
        if ((cmd.cmdName) == commandArg)
        {
            cmd.action();
            currentState = cmd.nextState;
            cmdSucessful = true;
        }
    }

    if (!cmdSucessful)
    {
        std::cout << "Invalid command. See above for valid commands" << std::endl;
    }
}

void GameEngine::operator=(GameState &newState)
{
    currentState = &newState;
}

std::ostream &operator<<(std::ostream &os, const GameEngine &gameEngine)
{
    os << "Current state = state " << gameEngine.currentState << std::endl;
    return os;
}
