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
    std::map<int, std::vector<std::string>> gameResults;

    // empty corner of the table
    gameResults[0].push_back("     ");
    for (int n = 0; n < numberOfGames; n++)
    {
        gameResults[0].push_back("Game " + std::to_string(n));
    }

    // For each map
    for (int k = 0; k < maps.size(); k++)
    {
        gameResults[k + 1].push_back("Map " + std::to_string(k + 1));
        gameEngine->gameMap = maps.at(k);
        // For each game on that map
        for (int i = 0; i < numberOfGames; i++)
        {
            // Setting the players of the tournament
            gameEngine->winner = nullptr;
            gameEngine->players->clear();
            for (auto player : players)
            {
                player->reset_player();
                gameEngine->players->push_back(player);
            }

            for (int j = 0; j <= maxTurns; j++)
            {
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
            gameResults[k + 1].push_back(results[k][i]);
        }
    }
    logResults(gameResults);
}

// rankedPlayerOrder should be in order of winner to loser
void Tournament::logResults(std::map<int, std::vector<std::string>> finalResults)
{
    {
        // std::ofstream file("/Users/zhzha/Desktop/COMP345_Warzone/Assignment_1/GameLog.txt", std::ios::app);
        std::ofstream file("GameLog.txt", std::ios::app);
        // std::ofstream file("GameLog.txt", std::ios::app);

        if (file.is_open())
        {
            // Write the log entry to the file
            file << "------------------------------------ TOURNAMENT RESULTS ---------------------------------" << std::endl;

            file << "Tournament Mode: " << endl;

            file << "M: ";
            for (int i = 0; i < maps.size(); i++)
            {
                file << maps[i]->mapName << "     ";
            }
            file << endl;

            file << "P: ";
            for (int j = 0; j < players.size(); j++)
            {
                file << players[j]->getPlayerName() << "     ";
            }
            file << endl;

            file << "G: " << numberOfGames << endl;
            file << "D: " << maxTurns << endl;
            file << "----------------------------------------------------------------------------------------" << std::endl;
            file << endl;

            // ACTUAL RESULT TABLE
            for (const auto &pair : finalResults)
            {
                file << "|";
                for (const auto &output : pair.second)
                {
                    file << "  " << output;
                }
                file << std::endl;
                file << "----------------------------------------------------------------------------------------" << std::endl;
            }

            // Close the file
            file.flush();
            file.close();
        }
        else
        {
            std::cerr << "Unable to open GameLog.txt for writing. Error code: " << errno << std::endl;
        }
    }
}