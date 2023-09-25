#include "GameEngine.h"


Command::Command(std::string cmdName, std::function<void()> action, GameState nextState) :
        cmdName(&cmdName),
        action(&action),
        nextState(&nextState) {}

Command::~Command() {}


GameEngine::GameEngine(GameState currentState, std::map<GameState, std::list<Command>> stateTransitions):
    currentState(&currentState), 
    stateTransitions(&stateTransitions) {}

GameEngine::~GameEngine() {}

void GameEngine::executeCommand(std::string commandArg)
{
    // Dereference pointers
    GameState cs = *(currentState);
    std::map<GameState, std::list<Command>> transitions = *(stateTransitions);

    std::list<Command> commands = transitions[cs];
    bool cmdSucessful = false;

    for (auto cmd : commands)
    {
        std::string* cmdName = cmd.cmdName;
        if (*cmdName == commandArg)
        {
            std::function<void()> a = *(cmd.action);
            a();
            // cmd.nextState is already a pointer don't need to dereference
            currentState = cmd.nextState;
            cmdSucessful = true;
        }
    }

    if (!cmdSucessful)
    {
        std::cout << "Invalid command. See above for valid commands" << std::endl;
    }
}
