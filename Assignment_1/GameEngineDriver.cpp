#include "GameEngine.h"
#include <string>


// Sample actions
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
    GameState START = GameState::START;
    GameState MAP_LOADED = GameState::MAP_LOADED;
    GameState MAP_VALIDATED = GameState::MAP_VALIDATED;
    GameState PLAYERS_ADDED = GameState::PLAYERS_ADDED;
    GameState ASSIGN_REINFORCEMENTS = GameState::ASSIGN_REINFORCEMENTS;
    GameState ISSUE_ORDERS = GameState::ISSUE_ORDERS;
    GameState EXECUTE_ORDERS = GameState::EXECUTE_ORDERS;
    GameState WIN = GameState::WIN;
    GameState END = GameState::END;

    std::string loadMapCmd= "loadMap";
    std::string validateMapCmd= "validateMap";
    std::string addPlayerCmd= "addPlayer";
    std::string assignCountriesCmd= "assignCountries";
    std::string issueOrderCmd= "issueOrder";
    std::string endIssueOrdersCmd= "endIssueOrders";
    std::string executeOrderCmd= "executeOrder";
    std::string endExecuteOrdersCmd= "endExecuteOrders";
    std::string winCmd= "win";
    std::string playCmd= "play";
    std::string endCmd= "end";

    // Game Engine FSM
    std::map<GameState, std::list<Command>> stateTransitions = {
        // Start states
        {GameState::START, { 
            Command(&loadMapCmd, &std::function<void()>(loadMap), &MAP_LOADED)}},
        {GameState::MAP_LOADED, {
            Command(&loadMapCmd, &std::function<void()>(loadMap), &MAP_LOADED),
            Command(&validateMapCmd, &std::function<void()>(validateMap), &MAP_VALIDATED)}},
        {GameState::MAP_VALIDATED, {
            Command(&addPlayerCmd, &std::function<void()>(addPlayer), &PLAYERS_ADDED)}},
        {GameState::PLAYERS_ADDED, {
            Command(&addPlayerCmd, &std::function<void()>(addPlayer), &PLAYERS_ADDED),
            Command(&assignCountriesCmd, &std::function<void()>(assignCountries), &ASSIGN_REINFORCEMENTS)}},
        // Play states
        {GameState::ASSIGN_REINFORCEMENTS, std::list<Command>{
            Command(&issueOrderCmd, &std::function<void()>(issueOrder), &ASSIGN_REINFORCEMENTS)}},
        {GameState::ISSUE_ORDERS,{
            Command(&issueOrderCmd, &std::function<void()>(issueOrder), &ISSUE_ORDERS),
            Command(&endIssueOrdersCmd, &std::function<void()>(endIssueOrders), &EXECUTE_ORDERS)}},
        {GameState::EXECUTE_ORDERS, {
            Command(&executeOrderCmd, &std::function<void()>(executeOrder), &EXECUTE_ORDERS),
            Command(&endExecuteOrdersCmd, &std::function<void()>(endExecuteOrders), &ASSIGN_REINFORCEMENTS),
            Command(&winCmd, &std::function<void()>(win), &WIN)}},
        {GameState::WIN, {
            Command(&playCmd, &std::function<void()>(start), &START),
            Command(&endCmd, &std::function<void()>(end), &END)}},
    };

    GameState currentState = GameState::START;
    GameEngine gameEngine(&currentState, &stateTransitions);

    start();
    while (*(gameEngine.currentState) != GameState::END)
    {
        std::cout << "> ";
        std::string command;
        std::cin >> command;
        gameEngine.executeCommand(command);
    }

}