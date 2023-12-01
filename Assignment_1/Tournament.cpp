#pragma once
#include "Tournament.h"
#include "GameEngine.h"

// Default constructor
Tournament::Tournament() {
    players = {};
    maps = {};
    numberOfGames = 0;
    maxTurns = 0;
}

// Parametrized constructor
Tournament::Tournament(int numberOfGames, int maxTurns) : numberOfGames(numberOfGames), maxTurns(maxTurns){}

// Copy constructor
  Tournament::Tournament(const Tournament &tournament) {
    players = vector<Player*>(tournament.players);
    maps = vector<Map*>(tournament.maps);
    numberOfGames = tournament.numberOfGames;
    maxTurns = tournament.maxTurns;
	gameEngine = new GameEngine(*tournament.gameEngine);
  }

// Destructor
Tournament::~Tournament() {
    for (auto player : players) {
        delete player;
        player = nullptr;
    }

    for (auto map : maps) {
        delete map;
        map = nullptr;
    }

	delete gameEngine;
	gameEngine = nullptr;
}   

// Assignment operator
Tournament& Tournament::operator=(const Tournament &tournament) {
    players = vector<Player*>(tournament.players);
    maps = vector<Map*>(tournament.maps);
    numberOfGames = tournament.numberOfGames;
    maxTurns = tournament.maxTurns;
	gameEngine = new GameEngine(*tournament.gameEngine);

    return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& os, const Tournament& tournament) {
    os << "Tournament: " << endl;
    os << "Strategies: " << endl;
    for (auto player : tournament.players) {
        os << *player << endl;
    }

    os << "Maps: " << endl;
    for (auto map : tournament.maps) {
        os << *map << endl;
    }

    os << "Number of games: " << tournament.numberOfGames << endl;
    os << "Max turns: " << tournament.maxTurns << endl;

    return os;
}

// Add a player to the tournament
void Tournament::addPlayer(Player* player) {
    players.push_back(player);
}

// Add a map to the tournament
void Tournament::addMap(Map* map) {
    maps.push_back(map);
}   

// Set the number of games to be played
void Tournament::setNumberOfGames(int numberOfGames) {
    this->numberOfGames = numberOfGames;
}

// Set the maximum number of turns per game
void Tournament::setMaxTurns(int maxTurns) {
    this->maxTurns = maxTurns;
}

// Function to play the tournament
void Tournament::play() {
	// Setting the players of the tournament
	gameEngine->players = &players;
    // For each map
    for (auto map : maps) {
		gameEngine->gameMap = map;
		// For each game on that map
        for (int i = 0; i < numberOfGames; i++) {

            //TODO: Finish implementation of play tournament
			// Basically for each game on a map, run the regular game loop until the game is over
			// or the max number of turns has been reached. Make sure that the strategies execute their functions
			// Automatically. Then 
        }
    }
}