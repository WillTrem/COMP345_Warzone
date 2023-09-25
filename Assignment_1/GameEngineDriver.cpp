#include "GameEngine.h"
#include <string>


// Temporary so that compiler doesn't complain
// TODO: Implement/replace the actual functions
void start()
{
    std::cout << "Started game\n"
              << std::endl;
    std::cout << "Available commands: 'loadMap'" << std::endl;
}
void loadMap()
{
    std::cout << "Loaded map sucessfully\n"
              << std::endl;
    std::cout << "Available commands: 'loadMap' , 'validateMap'" << std::endl;
}
void validateMap()
{
    std::cout << "Validated map sucessfully\n"
              << std::endl;
    std::cout << "Available commands: 'addPlayer'" << std::endl;
}
void addPlayer()
{
    std::cout << "Added player\n"
              << std::endl;
    std::cout << "Available commands: 'addPlayer' , 'assignCountries'" << std::endl;
}
void assignCountries()
{
    std::cout << "Assigned countries\n"
              << std::endl;
    std::cout << "Available commands: 'issueOrder'" << std::endl;
}
void issueOrder()
{
    std::cout << "Order issued sucessfully\n"
              << std::endl;
    std::cout << "Available commands: 'issueOrder' , 'endIssueOrders'" << std::endl;
}
void endIssueOrders()
{
    std::cout << "Done issuing orders\n"
              << std::endl;
    std::cout << "Available commands: 'executeOrder' , 'endExecuteOrders' , 'win'" << std::endl;
}
void executeOrder()
{
    std::cout << "Order executed sucessfully\n"
              << std::endl;
    std::cout << "Available commands: 'executeOrder' , 'endExecuteOrders' , 'win'" << std::endl;
}
void endExecuteOrders()
{
    std::cout << "Done executing orders\n"
              << std::endl;
    std::cout << "Available commands: 'issueOrder'" << std::endl;
}
void win()
{
    std::cout << "You win!\n"
              << std::endl;
    std::cout << "Available commands: 'play' , 'end'" << std::endl;
}
void end()
{
    std::cout << "Thank you for playing!\n"
              << std::endl;
}


void testGameEngine()
{
    // Game Engine FSM
    std::map<GameState, std::list<Command>> stateTransitions = {
        // Start states
        {GameState::START, std::list<Command>{
            Command("loadMap", [&]() { loadMap(); }, GameState::MAP_LOADED)}},
        {GameState::MAP_LOADED, std::list<Command>{
            Command( "loadMap", [&]() { loadMap(); }, GameState::MAP_LOADED),
            Command("validateMap", [&]() { validateMap(); }, GameState::MAP_VALIDATED)}},
        {GameState::MAP_VALIDATED, std::list<Command>{
            Command("addPlayer", [&]() { addPlayer(); }, GameState::PLAYERS_ADDED)}},
        {GameState::PLAYERS_ADDED, std::list<Command> {
            Command("addPlayer", [&]() { addPlayer(); }, GameState::PLAYERS_ADDED),
          Command("assignCountries", [&]() { assignCountries(); }, GameState::ASSIGN_REINFORCEMENTS)}},
        // Play states
        {GameState::ASSIGN_REINFORCEMENTS, std::list<Command>{
            Command("issueOrder", [&]() { issueOrder(); }, GameState::ISSUE_ORDERS)}},
        {GameState::ISSUE_ORDERS, std::list<Command>{
            Command("issueOrder", [&]() { issueOrder(); }, GameState::ISSUE_ORDERS),
            Command("endIssueOrders", [&]() { endIssueOrders(); }, GameState::EXECUTE_ORDERS)}},
        {GameState::EXECUTE_ORDERS, std::list<Command>{
            Command("executeOrder", [&]() { executeOrder(); }, GameState::EXECUTE_ORDERS),
            Command("endExecuteOrders", [&]() { endExecuteOrders(); }, GameState::ASSIGN_REINFORCEMENTS),
            Command("win", [&]() { win(); }, GameState::WIN)}},
        {GameState::WIN, std::list<Command>{
            Command("play", [&]() { start(); }, GameState::EXECUTE_ORDERS),
            Command("end", [&]() { end(); }, GameState::END)}},
    };

    GameEngine gameEngine(GameState::START, stateTransitions);

    start();
    while (*(gameEngine.currentState) != GameState::END)
    {
        std::cout << "> ";
        std::string command;
        std::cin >> command;
        gameEngine.executeCommand(command);
    }

}