#include "GameEngine.h"

Command::Command(std::string *cmdName, std::function<void()> *action, GameState *nextState):
        cmdName(cmdName),
        action(action),
        nextState(nextState) {}

GameEngine::GameEngine(GameState* currentState, std::map<GameState, std::list<Command>>* stateTransitions):
    currentState(currentState), 
    stateTransitions(stateTransitions) {}

void GameEngine::executeCommand(std::string commandArg)
{
    bool cmdSucessful = false;

    // passed by reference instead of value so no new variables are created
    for (auto &cmd : (*stateTransitions)[*currentState])
    {
        if ((*cmd.cmdName) == commandArg)
        {
            auto action = *cmd.action;
            action();
            currentState = cmd.nextState;
            cmdSucessful = true;
        }
    }

    if (!cmdSucessful)
    {
        std::cout << "Invalid command. See above for valid commands" << std::endl;
    }
}
