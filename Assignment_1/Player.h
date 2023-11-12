// PART 2.
//
// Implement a group of C++ classes that implement a Warzone player.
// Written by William Tremblay, 40174212.

#pragma once

#include <string>

#include "Cards.h"
#include "Map.h"

using namespace std;

// putting these forward declarations here to avoid circular dependency!
class OrdersList;
class Order;
class Deploy;

class Player
{
private:
	static int numPlayers;

	vector<Territory *> ownedTerritories;
	OrdersList *ordersList = nullptr;
	Hand *hand = nullptr;
	string *playerName;

	int reinforcementPool = 0;

	vector<Territory *> prioritizeTerritories(vector<Territory *> territories);

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

	vector<Territory *> getOwnedTerritories();
	void addOwnedTerritory(Territory *territory);
	Territory *removeOwnedTerritory(Territory *territory);

	OrdersList *getOrdersList();

	string getPlayerName();

	int getReinforcmentPool();
	void setReinforcementPool(int numUnits);

	// TODO
	vector<Territory *> toDefend();
	// TODO
	vector<Territory *> toAttack();

	void issueOrder(Order *order);

	// Assignment operator overload
	void operator=(Player &player);

	// Stream insertion operator overload
	friend std::ostream &operator<<(std::ostream &out, const Player &p);
};
