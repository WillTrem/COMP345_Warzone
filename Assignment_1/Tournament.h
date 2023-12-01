#include "Player.h"
#include "Map.h"

#include <vector>
#include <string>
#pragma once

using namespace std;

class GameEngine; // Forward declaration to avoid circular dependencies for the tournament implementation

class Tournament
{

public:
    vector<Player *> players;
    vector<Map *> maps;
    int numberOfGames;
    int maxTurns;
    GameEngine *gameEngine = nullptr;
    string results[5][5];

    // Default constructor
    Tournament();

    // Parametrized constructor
    Tournament(int numberOfGames, int maxTurns);

    // Copy constructor
    Tournament(const Tournament &tournament);

    // Destructor
    ~Tournament();

    // Assignment operator
    Tournament &operator=(const Tournament &tournament);

    // Stream insertion operator
    friend ostream &operator<<(ostream &os, const Tournament &tournament);

    // Add a player to the tournament
    void addPlayer(Player *player);

    // Add a map to the tournament
    void addMap(Map *map);

    // Set the number of games to be played
    void setNumberOfGames(int numberOfGames);

    // Set the maximum number of turns per game
    void setMaxTurns(int maxTurns);

    // Function to play the tournament
    void play();

    void logResults(const std::string &gameNo, const std::list<Player *> &rankedPlayerOrder);
};
