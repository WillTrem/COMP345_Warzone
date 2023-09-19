#include "GameEngine.h"

GameStateAction::GameStateAction(void (*a)(), GameState ns)
{
    nextState = ns;
    action = a;
}

// Temporary so that compiler doesn't complain
// TODO: replace with actual functions
void loadMap() {}
void validateMap() {}
void addPlayers() {}
void assignCountries() {}

GameEngine::GameEngine()
{
    stateTransitions = {
        // Start states
        {GameState::START, {GameStateAction(&loadMap, GameState::MAP_LOADED)}},
        {GameState::MAP_LOADED, {GameStateAction(&loadMap, GameState::MAP_LOADED)}},
        {GameState::MAP_LOADED, {GameStateAction(&validateMap, GameState::MAP_VALIDATED)}},
        {GameState::MAP_VALIDATED, {GameStateAction(&addPlayers, GameState::PLAYERS_ADDED)}},
        {GameState::PLAYERS_ADDED, {GameStateAction(&addPlayers, GameState::PLAYERS_ADDED)}},
        // Play states
        {GameState::PLAYERS_ADDED, {GameStateAction(&addPlayers, GameState::PLAYERS_ADDED)}},
        

    };
}
