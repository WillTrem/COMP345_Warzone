#pragma once
#include "Tournament.h"
#include "GameEngine.h"
#include "CommandProcessing.h"

// Default constructor
Tournament::Tournament()
{
    players = {};
    maps = {};
    numberOfGames = 0;
    maxTurns = 0;
}

// Parametrized constructor
Tournament::Tournament(int numberOfGames, int maxTurns) : numberOfGames(numberOfGames), maxTurns(maxTurns) {}

// Copy constructor
Tournament::Tournament(const Tournament &tournament)
{
    players = vector<Player *>(tournament.players);
    maps = vector<Map *>(tournament.maps);
    numberOfGames = tournament.numberOfGames;
    maxTurns = tournament.maxTurns;
    gameEngine = new GameEngine(*tournament.gameEngine);
}

// Destructor
Tournament::~Tournament()
{
    for (auto player : players)
    {
        delete player;
        player = nullptr;
    }

    for (auto map : maps)
    {
        delete map;
        map = nullptr;
    }

    delete gameEngine;
    gameEngine = nullptr;
}

// Assignment operator
Tournament &Tournament::operator=(const Tournament &tournament)
{
    players = vector<Player *>(tournament.players);
    maps = vector<Map *>(tournament.maps);
    numberOfGames = tournament.numberOfGames;
    maxTurns = tournament.maxTurns;
    gameEngine = new GameEngine(*tournament.gameEngine);

    return *this;
}

// Stream insertion operator
ostream &operator<<(ostream &os, const Tournament &tournament)
{
    os << "Tournament: " << endl;
    os << "Strategies: " << endl;
    for (auto player : tournament.players)
    {
        os << *player << endl;
    }

    os << "Maps: " << endl;
    for (auto map : tournament.maps)
    {
        os << *map << endl;
    }

    os << "Number of games: " << tournament.numberOfGames << endl;
    os << "Max turns: " << tournament.maxTurns << endl;

    return os;
}

// Add a player to the tournament
void Tournament::addPlayer(Player *player)
{
    players.push_back(player);
}

// Add a map to the tournament
void Tournament::addMap(Map *map)
{
    maps.push_back(map);
}

// Set the number of games to be played
void Tournament::setNumberOfGames(int numberOfGames)
{
    this->numberOfGames = numberOfGames;
}

// Set the maximum number of turns per game
void Tournament::setMaxTurns(int maxTurns)
{
    this->maxTurns = maxTurns;
}

// Function to play the tournament
void Tournament::play()
{
    GameState assignReinforcements = ASSIGN_REINFORCEMENTS;

    // For each map
    for (int k = 0; k < maps.size(); k++)
    {
        gameEngine->gameMap = maps.at(k);
        // For each game on that map
        for (int i = 0; i < numberOfGames; i++)
        {
            // Setting the players of the tournament
            gameEngine->players->clear();
            for (auto player : players)
            {
                gameEngine->players->push_back(new Player(*player));
            }

<<<<<<< Updated upstream
            for (int j = 0; j < maxTurns; j++)
            {
=======
            for (int j = 0; j <= maxTurns; j++){
>>>>>>> Stashed changes
                // If a player has won the game
                if (gameEngine->winner != nullptr)
                {
                    results[k][i] = gameEngine->winner->getPlayerName();
                    gameEngine->currentState = &assignReinforcements;
                    break;
                }
                else if (j == maxTurns)
                {
                    results[k][i] = "Draw";
                    gameEngine->currentState = &assignReinforcements;
                    break;
                }
                
                gameEngine->mainGameLoop();
            }
            logResults(i + 1, );
        }
    }
}

// rankedPlayerOrder should be in order of winner to loser
void Tournament::logResults(const std::int &gameNo, const std::list<Player *> &rankedPlayerOrder)
{
    {
        std::ofstream file("/Users/zhzha/Desktop/COMP345_Warzone/Assignment_1/GameLog.txt", std::ios::app);
        // std::ofstream file("Assignment_1/GameLog.txt", std::ios::app);
        // std::ofstream file("GameLog.txt", std::ios::app);

        if (file.is_open())
        {
            // Write the log entry to the file
            file << "------------------------------------ TOURNAMENT RESULTS ---------------------------------" << std::endl;
            file << "|___|___|___|" << std::endl;

            file << "|___|___|___|" << std::endl;

            file << "| " << placeholder1 << "| " << placeholder2 << "| " << placeholder3 << "|" << std::endl;

            file << "|___|___|___|" << std::endl;

            // Close the file
            file.flush();
            file.close();
        }
        else
        {
            std::cerr << "Unable to open GameLog.txt for writing. Error code: " << errno << std::endl;
        }
    }