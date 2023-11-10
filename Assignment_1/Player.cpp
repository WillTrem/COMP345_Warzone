// PART 2.
//
// Implement a group of C++ classes that implement a Warzone player.
// Written by William Tremblay, 40174212.

#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

using namespace std;

int Player::numPlayers = 0;

// Default constructor
Player::Player()
{
	hand = new Hand();
	ownedTerritories = {new Territory(), new Territory(), new Territory()};
	ordersList = new OrdersList();

	numPlayers++;
	playerName = new string("Player " + std::to_string(numPlayers)); // Make sure no player has the same name.
}

// Parametrized constructorw
Player::Player(string name)
{
	hand = new Hand();
	ownedTerritories = {}; // new Territory(), new Territory(), new Territory()
	ordersList = new OrdersList();

	numPlayers++;
	playerName = new string(name + " " + std::to_string(numPlayers));
}
Player::Player(Hand *initialHand, vector<Territory *> &initialTerritories, string name)
{
	hand = initialHand;
	ownedTerritories = initialTerritories;
	ordersList = new OrdersList();

	numPlayers++;
	playerName = new string(string(name) + " " + std::to_string(numPlayers));
}

// Copy constructor
Player::Player(const Player &player)
{
	hand = new Hand(player.hand);
	ownedTerritories = vector<Territory *>(player.ownedTerritories);
	ordersList = new OrdersList(*player.ordersList);

	numPlayers++;
	playerName = new string(*(player.playerName) + " " + std::to_string(numPlayers));
}

Player::~Player()
{
	cout << "Player destructor called" << endl;

	// Delete name.
	delete playerName;
	playerName = NULL;

	// Calling other destructors
	hand->~Hand();
	ordersList->~OrdersList();

	// Memory deallocation
	// delete hand;
	// delete ordersList;

	// Setting pointers to null
	hand = NULL;
	ordersList = NULL;

	// Repeating the same steps for each of the territories of the player
	for (int i = 0; i < ownedTerritories.size(); i++)
	{
		ownedTerritories.at(i)->~Territory();
		// delete ownedTerritories.at(i);
		ownedTerritories.at(i) = NULL;
	}
}

// Returns the player's name
string Player::getPlayerName()
{
	return *playerName;
}

int Player::getReinforcmentPool()
{
	return reinforcementPool;
}

void Player::setReinforcementPool(int numUnits)
{
	reinforcementPool = numUnits;
}

// Returns the hand of the player
Hand *Player::getHand()
{
	return hand;
}

// Returns the player's current orders list
OrdersList *Player::getOrdersList()
{
	return ordersList;
}

// Returns the player's collection of currently owned territories
vector<Territory *> Player::getOwnedTerritories()
{
	return ownedTerritories;
}

// Pushes a new territory onto the player's list of owned territories.
void Player::addOwnedTerritory(Territory *territory)
{

	// Should we check whether the territory is already present there?
	ownedTerritories.push_back(territory);
}

// Pops an existing territory from the player's list of owned territories. Returns its reference.
Territory *Player::removeOwnedTerritory(Territory *territory)
{
	// Find the territory in the vector.
	auto it = find(ownedTerritories.begin(), ownedTerritories.end(), territory);

	// Remove it
	if (it != ownedTerritories.end())
	{
		Territory *popppedTerritory = *it;
		ownedTerritories.erase(it);

		return popppedTerritory;
	}
	return nullptr; // If the territory was not found in the vector, simply return the nullpointer.
}

// Returns an arbitrary list of territories to Defend
vector<Territory *> Player::toDefend()
{
	// Prioritize territory to defend
	vector<Territory *> territoriesToDefend;
	vector<Territory *> ownedTerritories = getOwnedTerritories();
	for (int i = 0; i < ownedTerritories.size(); i++)
	{
		std::cout << "Prioritize which territory to attack: priority " << i + 1 << std::endl;
		for (int j = 0; j < ownedTerritories.size(); j++)
		{
			std::cout << ownedTerritories[j]->territoryName << "? (y/n) " << std::endl;
			string answer;
			std::cin >> answer;
			if (answer.compare("y") == 0)
			{
				territoriesToDefend.push_back(ownedTerritories[j]);
				break;
			}
		}

		// If user didn't say yes to any of them, restart last iteration
		if (territoriesToDefend.size() < i + 1)
		{
			i--;
		}
	}
}

// Returns an arbitrary list of territories to attack
vector<Territory *> Player::toAttack()
{

	// Retrieve all enemy neighboring territories
	vector<Territory *> enemyTerritories;
	for (auto territory : getOwnedTerritories())
	{
		for (auto neighbor : territory->neighboringTerritories)
		{
			if (neighbor->occupierName.compare(*playerName) != 0)
			{
				enemyTerritories.push_back(neighbor);
			}
		}
	}

	// Prioritize territory to attack
	vector<Territory *> territoriesToAttack;
	for (int i = 0; i < enemyTerritories.size(); i++)
	{
		std::cout << "Prioritize which territory to attack: priority " << i + 1 << std::endl;
		for (int j = 0; j < enemyTerritories.size(); j++)
		{
			std::cout << enemyTerritories[j]->territoryName << "? (y/n) " << std::endl;
			string answer;
			std::cin >> answer;
			if (answer.compare("y") == 0)
			{
				territoriesToAttack.push_back(enemyTerritories[j]);
				break;
			}
		}

		// If user didn't say yes to any of them, restart last iteration
		if (territoriesToAttack.size() < i + 1)
		{
			i--;
		}
	}

	return territoriesToAttack;
}

// Creates a new order and adds it to the player's list of current orders
void Player::issueOrder(Order *order)
{
	// Order *newOrder = new Order();

	// ordersList->addOrder(newOrder);

	// TEMPORARILY REMOVED THE ABOVE LINES -- this function will be implemented with Part 3

	cout << "An order has been issued" << endl;
}

// Assignment operator overload
void Player::operator=(Player &player)
{
	cout << "Player assignment operator called." << endl;
	hand = player.hand;
	ordersList = player.ordersList;
	ownedTerritories = player.ownedTerritories;
}

// Stream insertion operator overload for class Player
ostream &operator<<(ostream &os, const Player &p)
{
	cout << "Player stream insertion operator called\n"
		 << endl;
	cout << "Player information:" << endl;
	cout << "Name: " << p.playerName << endl;
	cout << "\t Current hand: " << p.hand << endl;
	// cout << "\t Current orders list: "<<p.ordersList<<endl;

	// TODO: add territories when stream insertion operator is defined for them
	return os;
}
