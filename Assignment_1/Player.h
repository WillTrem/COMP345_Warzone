// PART 2.
//
// Implement a group of C++ classes that implement a Warzone player.
// Written by William Tremblay, 40174212.

#pragma once

#include <string>

#include "Cards.h"
#include "Map.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

// forward declaration to avoid circular hell
class PlayerStrategy;

// putting these forward declarations here to avoid circular dependency!
class OrdersList;
class Order;
class Deploy;

class Player
{
private:
	static int numPlayers;

	PlayerStrategy *ps; // player strategy
	vector<Territory *> ownedTerritories;
	OrdersList *ordersList = nullptr;
	Hand *hand = nullptr;
	string *playerName;

	int reinforcementPool = 0;
	vector<Territory *> prioritizeTerritories(vector<Territory *> territories);

	// attributes added to help with A2 Part 4 (order implementation)
	bool capturedTerritoryThisTurn = false;
	bool negotiate = false;

	// Do the other strategy types also need to be made friends?
	friend class PlayerStrategy;
	friend class HumanPlayerStrategy;
	friend class AggressivePlayerStrategy;
	friend class BenevolentPlayerStrategy;

public:
	int totalPlayerArmy = 0;
	int totalNumberOfTerritories = 0;

	// Default constructor
	Player();

	// Parametrized constructors
	Player(string name);
	Player(Hand *initialHand, vector<Territory *> &initialTerritories, string name = "Player");

	// Copy constructor
	Player(const Player &player);

	// Destructor
	~Player();

	// Getters and setters.
	Hand *getHand();

	// Set strategy for the computer player
	void setStrategy(PlayerStrategy *ps);

	PlayerStrategy *getStrategy();
	vector<Territory *> getOwnedTerritories() const;
	void addOwnedTerritory(Territory *territory);
	Territory *removeOwnedTerritory(Territory *territory);

	OrdersList *getOrdersList();

	string getPlayerName();

	int getReinforcmentPool();
	void setReinforcementPool(int numUnits);

	// methods added for A2 Part 4 (order implementation)
	void setCapturedTerritoryThisTurn(bool update);
	bool getCapturedTerritoryThisTurn();
	void setNegotiate(bool update);
	bool getNegotiate();

	// Wrapper methods for toAttack and toDefend.
	void toDefend();
	void toAttack();

	bool issueOrder();

	// Storage for the player's attack and defence targets.
	vector<Territory *> territoriesToDefend;
	vector<Territory *> territoriesToAttack;

	// method for part 1 of assg 3: update total number of player army across all owned territories
	int updateTotalPlayerArmyCount();

	// method for part 1 of assg 3: update total number of territory across all owned territories
	int updateTotalPlayerTerritoryCount();

	// method for part 1 of assg 3: get total number of player army across all owned territories
	int getTotalPlayerArmy();

	// method for part 1 of assg 3: get total number of territories
	int getNumberOfTerritories();

	// method for part 1 of assg 3: check if the player is attacked or not
	bool isNeutralPlayerAttacked();

	// Assignment operator overload
	void operator=(Player &player);

	// Stream insertion operator overload
	friend std::ostream &operator<<(std::ostream &out, const Player &p);
};
#endif