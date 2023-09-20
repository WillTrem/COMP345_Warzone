#include "GameEngine.h"

Command::Command(std::string _cmdName, void (*_action)(), GameState _nextState)
{
    cmdName = _cmdName;
    action = _action;
    nextState = _nextState;
}

// Temporary so that compiler doesn't complain
// TODO: Implement/replace the actual functions
void start()
{
    std::cout << "Started game" << std::endl;
    std::cout << "Available commands: 'loadMap'" << std::endl;
}
void loadMap()
{
    std::cout << "Loaded map sucessfully" << std::endl;
    std::cout << "Available commands: 'loadMap' , 'validateMap'" << std::endl;
}
void validateMap()
{
    std::cout << "Validated map sucessfully" << std::endl;
    std::cout << "Available commands: 'addPlayer'" << std::endl;
}
void addPlayer()
{
    std::cout << "Added player" << std::endl;
    std::cout << "Available commands: 'addPlayer' , 'assignCountries'" << std::endl;
}
void assignCountries()
{
    std::cout << "Assigned countries" << std::endl;
    std::cout << "Available commands: 'issueOrder'" << std::endl;
}
void issueOrder()
{
    std::cout << "Issue ordered sucessfully" << std::endl;
    std::cout << "Available commands: 'issueOrder' , 'endIssueOrders'" << std::endl;
}
void endIssueOrders()
{
    std::cout << "Done issuing orders" << std::endl;
    std::cout << "Available commands: 'executeOrder' , 'endExecuteOrders' , 'win'" << std::endl;
}
void executeOrder()
{
    std::cout << "Executed order sucessfully" << std::endl;
    std::cout << "Available commands: 'executeOrder' , 'endExecuteOrders' , 'win'" << std::endl;
}
void endExecuteOrders()
{
    std::cout << "Done executing orders" << std::endl;
    std::cout << "Available commands: 'issueOrder'" << std::endl;
}
void win()
{
    std::cout << "You win!" << std::endl;
    std::cout << "Available commands: 'play' , 'end'" << std::endl;
}
void end()
{
    std::cout << "Thank you for playing!" << std::endl;
}

GameEngine::GameEngine()
{
    currentState = GameState::START;

    start();

    stateTransitions = {
        // Start states
        {GameState::START,
         {Command("loadMap", &loadMap, GameState::MAP_LOADED)}},
        {GameState::MAP_LOADED,
         {Command("loadMap", &loadMap, GameState::MAP_LOADED),
          Command("validateMap", &validateMap, GameState::MAP_VALIDATED)}},
        {GameState::MAP_VALIDATED,
         {Command("addPlayer", &addPlayer, GameState::PLAYERS_ADDED)}},
        {GameState::PLAYERS_ADDED,
         {Command("addPlayer", &addPlayer, GameState::PLAYERS_ADDED),
          Command("assignCountries", &assignCountries, GameState::ASSIGN_REINFORCEMENTS)}},
        // Play states
        {GameState::ASSIGN_REINFORCEMENTS,
         {Command("issueOrder", &issueOrder, GameState::ISSUE_ORDERS)}},
        {GameState::ISSUE_ORDERS,
         {Command("issueOrder", &issueOrder, GameState::ISSUE_ORDERS),
          Command("endIssueOrders", &endIssueOrders, GameState::EXECUTE_ORDERS)}},
        {GameState::EXECUTE_ORDERS,
         {Command("executeOrder", &executeOrder, GameState::EXECUTE_ORDERS),
          Command("endExecuteOrders", &endExecuteOrders, GameState::ASSIGN_REINFORCEMENTS),
          Command("win", &win, GameState::WIN)}},
        {GameState::WIN,
         {Command("play", &start, GameState::EXECUTE_ORDERS),
          Command("endExecuteOrders", &endExecuteOrders, GameState::ASSIGN_REINFORCEMENTS)}},

    };
}

void GameEngine::executeCommand(std::string commandArg)
{
    std::list<Command> commands = stateTransitions[currentState];
    bool cmdSucessful = false;

    for (auto cmd : commands)
    {
        if (cmd.cmdName == commandArg)
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
