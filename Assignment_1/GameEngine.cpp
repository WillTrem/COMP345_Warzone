#include "GameEngine.h"


Command::Command(std::string cmdName, std::function<void()> action, GameState nextState) :
        cmdName(cmdName),
        action(action),
        nextState(nextState) {}


GameEngine::GameEngine(GameState* currentState, std::map<GameState, std::list<Command>>* stateTransitions):
    currentState(currentState), 
    stateTransitions(stateTransitions) {}

void GameEngine::executeCommand(std::string commandArg)
{
    // Dereference pointers
    GameState cs = *(currentState);
    bool cmdSucessful = false;

    for (auto &cmd : (*stateTransitions)[cs])
    {
        if (cmd.cmdName == commandArg)
        {
            cmd.action();
            // cmd.nextState is already a pointer don't need to dereference
            currentState = &cmd.nextState;
            cmdSucessful = true;
        }
    }

    if (!cmdSucessful)
    {
        std::cout << "Invalid command. See above for valid commands" << std::endl;
    }
}
