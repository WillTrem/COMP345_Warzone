#include "GameEngine.h"


// Temporary so that compiler doesn't complain
// TODO: Implement/replace the actual functions
void GameEngine::start()
{
    std::cout << "Started game\n"
              << std::endl;
    std::cout << "Available commands: 'loadMap'" << std::endl;
}
void GameEngine::loadMap()
{
    std::cout << "Loaded map sucessfully\n"
              << std::endl;
    std::cout << "Available commands: 'loadMap' , 'validateMap'" << std::endl;
}
void GameEngine::validateMap()
{
    std::cout << "Validated map sucessfully\n"
              << std::endl;
    std::cout << "Available commands: 'addPlayer'" << std::endl;
}
void GameEngine::addPlayer()
{
    std::cout << "Added player\n"
              << std::endl;
    std::cout << "Available commands: 'addPlayer' , 'assignCountries'" << std::endl;
}
void GameEngine::assignCountries()
{
    std::cout << "Assigned countries\n"
              << std::endl;
    std::cout << "Available commands: 'issueOrder'" << std::endl;
}
void GameEngine::issueOrder()
{
    std::cout << "Order issued sucessfully\n"
              << std::endl;
    std::cout << "Available commands: 'issueOrder' , 'endIssueOrders'" << std::endl;
}
void GameEngine::endIssueOrders()
{
    std::cout << "Done issuing orders\n"
              << std::endl;
    std::cout << "Available commands: 'executeOrder' , 'endExecuteOrders' , 'win'" << std::endl;
}
void GameEngine::executeOrder()
{
    std::cout << "Order executed sucessfully\n"
              << std::endl;
    std::cout << "Available commands: 'executeOrder' , 'endExecuteOrders' , 'win'" << std::endl;
}
void GameEngine::endExecuteOrders()
{
    std::cout << "Done executing orders\n"
              << std::endl;
    std::cout << "Available commands: 'issueOrder'" << std::endl;
}
void GameEngine::win()
{
    std::cout << "You win!\n"
              << std::endl;
    std::cout << "Available commands: 'play' , 'end'" << std::endl;
}
void GameEngine::end()
{
    std::cout << "Thank you for playing!\n"
              << std::endl;
}

Command::Command(std::string _cmdName, std::function<void()> _action, GameState _nextState)
{
    cmdName = new std::string(_cmdName);
    action = new  std::function<void()>(_action);
    nextState = new GameState(_nextState);
}

Command::~Command()
{
    delete cmdName;
    delete action;
    delete nextState;
}


GameEngine::GameEngine()
{
    
    currentState = new GameState(GameState::START);

    start();

    stateTransitions = new std::map<GameState, std::list<Command>>({
        // Start states
        {GameState::START, {
            Command("loadMap", [&]() { loadMap(); }, GameState::MAP_LOADED)}},
        {GameState::MAP_LOADED, {
            Command( "loadMap", [&]() { loadMap(); }, GameState::MAP_LOADED),
          Command("validateMap", [&]() { validateMap(); }, GameState::MAP_VALIDATED)}},
        {GameState::MAP_VALIDATED, {
            Command("addPlayer", [&]() { addPlayer(); }, GameState::PLAYERS_ADDED)}},
        {GameState::PLAYERS_ADDED, {
            Command("addPlayer", [&]() { addPlayer(); }, GameState::PLAYERS_ADDED),
          Command("assignCountries", [&]() { assignCountries(); }, GameState::ASSIGN_REINFORCEMENTS)}},
        // Play states
        {GameState::ASSIGN_REINFORCEMENTS, {
            Command("issueOrder", [&]() { issueOrder(); }, GameState::ISSUE_ORDERS)}},
        {GameState::ISSUE_ORDERS, {
            Command("issueOrder", [&]() { issueOrder(); }, GameState::ISSUE_ORDERS),
            Command("endIssueOrders", [&]() { endIssueOrders(); }, GameState::EXECUTE_ORDERS)}},
        {GameState::EXECUTE_ORDERS, {
            Command("executeOrder", [&]() { executeOrder(); }, GameState::EXECUTE_ORDERS),
            Command("endExecuteOrders", [&]() { endExecuteOrders(); }, GameState::ASSIGN_REINFORCEMENTS),
            Command("win", [&]() { win(); }, GameState::WIN)}},
        {GameState::WIN, {
            Command("play", [&]() { start(); }, GameState::EXECUTE_ORDERS),
            Command("end", [&]() { end(); }, GameState::END)}},
    });

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
