#include "GameEngine.h"

ActionState::ActionState(void (*a)(), GameState ns)
{
    nextState = ns;
    action = a;
}

// Temporary so that compiler doesn't complain
// TODO: Implement/replace the actual functions
void loadMap() {}
void validateMap() {}
void addPlayers() {}
void assignCountries() {}
void issueOrder() {}
void endIssueOrders() {}
void executeOrder() {}
void endExecuteOrders() {}
void win() {}
void play() {}
void end() {}

GameEngine::GameEngine()
{
    stateTransitions = {
        // Start states
        {GameState::START,
         {ActionState(&loadMap, GameState::MAP_LOADED)}},
        {GameState::MAP_LOADED,
         {ActionState(&loadMap, GameState::MAP_LOADED),
          ActionState(&validateMap, GameState::MAP_VALIDATED)}},
        {GameState::MAP_VALIDATED,
         {ActionState(&addPlayers, GameState::PLAYERS_ADDED)}},
        {GameState::PLAYERS_ADDED,
         {ActionState(&addPlayers, GameState::PLAYERS_ADDED),
          ActionState(&assignCountries, GameState::ASSIGN_REINFORCEMENTS)}},
        // Play states
        {GameState::ASSIGN_REINFORCEMENTS,
         {ActionState(&issueOrder, GameState::ISSUE_ORDERS)}},
        {GameState::ISSUE_ORDERS,
         {ActionState(&issueOrder, GameState::ISSUE_ORDERS),
          ActionState(&endIssueOrders, GameState::EXECUTE_ORDERS)}},
        {GameState::EXECUTE_ORDERS,
         {ActionState(&executeOrder, GameState::EXECUTE_ORDERS),
          ActionState(&endExecuteOrders, GameState::ASSIGN_REINFORCEMENTS),
          ActionState(&win, GameState::WIN)}},
        {GameState::WIN,
         {ActionState(&play, GameState::EXECUTE_ORDERS),
          ActionState(&endExecuteOrders, GameState::ASSIGN_REINFORCEMENTS)}},

    };
}
