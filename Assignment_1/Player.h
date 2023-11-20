// PART 2.
//
// Implement a group of C++ classes that implement a Warzone player.
// Written by William Tremblay, 40174212.

#pragma once

#include <string>

#include "Cards.h"
#include "Map.h"

using namespace std;

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
	int totalPlayerArmy = 0;
	vector<Territory *> prioritizeTerritories(vector<Territory *> territories);

	// attributes added to help with A2 Part 4 (order implementation)
	bool capturedTerritoryThisTurn = false;
	bool negotiate = false;

public:
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

	vector<Territory *> getOwnedTerritories();
	void addOwnedTerritory(Territory *territory);
	Territory *removeOwnedTerritory(Territory *territory);

	OrdersList *getOrdersList();

	string getPlayerName();

	int getReinforcmentPool();
	void setReinforcementPool(int numUnits);

	// methods added for A2 Part 4 (order implementation)
	void setCapturedTerritoryThisTurn(bool update);
	void setNegotiate(bool update);
	bool getNegotiate();

	// TODO
	vector<Territory *> toDefend();
	// TODO
	vector<Territory *> toAttack();

	void issueOrder(Order *order);

	// method for part 1 of assg 3: update total number of player army across all owned territories
	void updateTotalPlayerArmyCount();

	// method for part 1 of assg 3: get total number of player army across all owned territories
	int getTotalPlayerArmy();

	// Assignment operator overload
	void operator=(Player &player);

	// Stream insertion operator overload
	friend std::ostream &operator<<(std::ostream &out, const Player &p);
};
