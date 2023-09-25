#include "GameEngine.h"


Command::Command(std::string cmdName, std::function<void()> action, GameState nextState) :
        cmdName(new std::string(cmdName)),
        action(new std::function<void()>(action)),
        nextState(new GameState(nextState))
{}

Command::~Command()
{
    delete cmdName;
    delete action;
    delete nextState;
}


GameEngine::GameEngine(GameState currentState, std::map<GameState, std::list<Command>> stateTransitions):
    currentState(new GameState(currentState)), 
    stateTransitions(new std::map<GameState, std::list<Command>>(stateTransitions))
{
    std::cout << "done constructing";
}

GameEngine::~GameEngine()
{
    delete currentState;
    delete stateTransitions;
}

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
