// PART 2.
//
// Implement a group of C++ classes that implement a Warzone player.
// Written by William Tremblay, 40174212.

#include "Orders.h" // put this here to avoid circular dependency
#include "PlayerStrategy.h"

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

// Parametrized constructor
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
	playerName = nullptr;

	// Calling other destructors
	this->hand->~Hand();
	this->ordersList->~OrdersList();

	// Memory deallocation
	// delete hand;
	// delete ordersList;

	// Setting pointers to null
	hand = nullptr;
	ordersList = nullptr;

	// Repeating the same steps for each of the territories of the player
	for (int i = 0; i < ownedTerritories.size(); i++)
	{
		ownedTerritories.at(i)->~Territory();
		// delete ownedTerritories.at(i);
		delete ownedTerritories.at(i);
		ownedTerritories.at(i) = nullptr;
	}
}

// Returns the player's name
string Player::getPlayerName()
{
	return *playerName;
}

void Player::setStrategy(PlayerStrategy *strategy)
{
	// cout << "Player is set to strategy : " << *strategy << endl;
	this->ps = strategy;
}

PlayerStrategy *Player::getStrategy()
{
	return this->ps;
}

int Player::getReinforcmentPool()
{
	return reinforcementPool;
}

void Player::setReinforcementPool(int numUnits)
{
	reinforcementPool = numUnits;
}

// set true to keep track of players who have captured a territory (they get a card this turn)
void Player::setCapturedTerritoryThisTurn(bool update)
{
	this->capturedTerritoryThisTurn = update;
}

// getter for capturedTerritoryThisTurn
bool Player::getCapturedTerritoryThisTurn()
{
	return this->capturedTerritoryThisTurn;
}

// setter flag to prevent attacks
void Player::setNegotiate(bool update)
{
	this->negotiate = update;
}

// getter flag to prevent attacks
bool Player::getNegotiate()
{
	return this->negotiate;
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
vector<Territory *> Player::getOwnedTerritories() const
{
	return ownedTerritories;
}

// Pushes a new territory onto the player's list of owned territories.
void Player::addOwnedTerritory(Territory *territory)
{
	territory->occupier = this;
	territory->occupierName = this->getPlayerName();
	ownedTerritories.push_back(territory);
	// Should we check whether the territory is already present there?
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

		territory->occupier = nullptr;
		territory->occupierName = "none";
		ownedTerritories.erase(it);

		return popppedTerritory;
	}
	return nullptr; // If the territory was not found in the vector, simply return the nullpointer.
}

vector<Territory *> Player::prioritizeTerritories(vector<Territory *> territories)
{
	vector<Territory *> territoriesPrioritized;
	for (int i = 0; i < territories.size(); i++)
	{
		std::cout << "Prioritize which territory to attack: priority " << i + 1 << std::endl;
		for (int j = 0; j < territories.size(); j++)
		{
			std::cout << territories[j]->territoryName << "? (y/n) " << std::endl;
			string answer;
			std::cin >> answer;
			if (answer.compare("y") == 0)
			{
				territoriesPrioritized.push_back(territories[j]);
				break;
			}
		}

		// If user didn't say yes to any of them, restart last iteration
		if (territoriesPrioritized.size() < i + 1)
		{
			i--;
		}
	}

	return territoriesPrioritized;
}

//// Returns an arbitrary list of territories to Defend
// vector<Territory *> Player::toDefend()
//{
//	// Prioritize territory to defend
//	vector<Territory *> ownedTerritories = ps->toDefend();
//	return prioritizeTerritories(ownedTerritories);
// }
//
//// Returns an arbitrary list of territories to attack
// vector<Territory *> Player::toAttack()
//{
//	// We could use the method in PlayerStrategy for this, which ensures there are no repeats in the vector?
//	// Retrieve all enemy neighboring territories
//
//	vector<Territory *> enemyTerritories;
//	// for (auto territory : getOwnedTerritories())
//	// {
//	// 	for (auto neighbor : territory->neighboringTerritories)
//	// 	{
//	// 		if (neighbor->occupierName.compare(*playerName) != 0)
//	// 		{
//	// 			enemyTerritories.push_back(neighbor);
//	// 		}
//	// 	}
//	// }
//	enemyTerritories = ps->toAttack();
//
//	// Prioritize territory to attack
//	return prioritizeTerritories(enemyTerritories);
// }

// Call toAttack() from within the player's strategy.
void Player::toAttack()
{
	this->territoriesToAttack = ps->toAttack();
}

// Call toDefend() from within the player's strategy.
void Player::toDefend()
{
	this->territoriesToDefend = ps->toDefend();
}

// Creates a new order and adds it to the player's list of current orders
bool Player::issueOrder(bool populateVectors)
{
	bool result = ps->issueOrder(populateVectors);
	return result;
}

// Assignment operator overload
void Player::operator=(Player &player)
{
	cout << "Player assignment operator called." << endl;
	hand = player.hand;
	ordersList = player.ordersList;
	ownedTerritories = player.ownedTerritories;
}

// Method to get player army count across their territories
int Player::getTotalPlayerArmy()
{
	return totalPlayerArmy;
}

int Player::getNumberOfTerritories()
{
	return totalNumberOfTerritories;
}
// Method to update player army count across their territories
int Player::updateTotalPlayerArmyCount()
{
	int numOfTroops = 0;
	for (Territory *territory : ownedTerritories)
	{
		numOfTroops = numOfTroops + territory->numOfArmies;
	}
	totalPlayerArmy = numOfTroops;
	return totalPlayerArmy;
}

int Player::updateTotalPlayerTerritoryCount()
{
	totalNumberOfTerritories = ownedTerritories.size();
	return totalNumberOfTerritories;
}

bool Player::isNeutralPlayerAttacked()
{
	int previousTotalPlayerArmy = totalPlayerArmy;
	cout << "Previous total player army count: " << previousTotalPlayerArmy << endl;
	int currentTotalPlayerArmy = updateTotalPlayerArmyCount();
	cout << "Current total player army count: " << currentTotalPlayerArmy << endl;

	int previousTotalNumberOfTerritories = totalNumberOfTerritories;
	cout << "Previous total player territory count: " << previousTotalNumberOfTerritories << endl;
	int currentTotalNumberOfTerritories = updateTotalPlayerTerritoryCount();
	cout << "Current total player territory count: " << currentTotalNumberOfTerritories << endl;
	if (currentTotalPlayerArmy < previousTotalPlayerArmy || (currentTotalNumberOfTerritories < previousTotalNumberOfTerritories && previousTotalNumberOfTerritories != 0 && currentTotalNumberOfTerritories != 0)) // Compare army before and army after update
	{
		cout << "NEUTRAL PLAYER IS ATTACKED!!!" << endl;
		cout << "NEUTRAL PLAYER IS NOW AGGRESSIVE" << endl;
		this->setStrategy(new AggressivePlayerStrategy(this));
		return true;
	}

	cout << "Player has not been attacked" << endl;
	return false;
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
