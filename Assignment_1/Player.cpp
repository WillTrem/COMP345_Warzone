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
	if (this->playerName == nullptr)
	{
		delete this->playerName;
		this->playerName = NULL;
	}

	// Calling other destructors
	this->hand->~Hand();
	this->ordersList->~OrdersList();

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

void Player::setStrategy(PlayerStrategy *strategy)
{
	this->ps = strategy;
}

int Player::getReinforcmentPool()
{
	return reinforcementPool;
}

void Player::setReinforcementPool(int numUnits)
{
	reinforcementPool = numUnits;
}

// for issuing a card to players who have captured a territory
void Player::setCapturedTerritoryThisTurn(bool update)
{
	this->capturedTerritoryThisTurn = update;
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
//vector<Territory *> Player::toDefend()
//{
//	// Prioritize territory to defend
//	vector<Territory *> ownedTerritories = ps->toDefend();
//	return prioritizeTerritories(ownedTerritories);
//}
//
//// Returns an arbitrary list of territories to attack
//vector<Territory *> Player::toAttack()
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
//}

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
void Player::issueOrder(Order *order)
{	
	// update the lists of territories to attack and defend
	this->toAttack();
	this->toDefend();

	// if player has reinforcement units, they must make a Deploy order!
	if (this->reinforcementPool > 0)
	{
		// logic needed to create a Deploy order:
		string territoryList = "";
		for (int i = 0; i < territoriesToDefend.size(); i++)
		{
			territoryList += territoriesToDefend[i]->territoryName + "( " + std::to_string(i) + " ), ";
		}

		int unitsDeployed = 0;
		
		std::cout << "Deploy units to which territory? " << territoryList << std::endl;
		string territory;
		std::cin >> territory;
		int tIndex = std::stoi(territory);

		if (!(tIndex >= 0 && tIndex < territoriesToDefend.size()))
		{
			std::cout << "Invalid territory number/index" << std::endl;
		}

		std::cout << "How many units? " << std::endl;
		string units;
		std::cin >> units;
		int unitsI = std::stoi(units);

		// must add function to get POINTER to the territory for Deploy constructor

		if (unitsI > 0 && unitsI + unitsDeployed <= this->getReinforcmentPool())
		{
			//this->ordersList->addOrder(Deploy(this, unitsI, territoryPtr));
			unitsDeployed += unitsI;
		}
		else
		{
			std::cout << "Invalid number of units (1 - units left in pool) " << std::endl;
		}
		
	}
	// if no more reinforcements, player can now do advance and attack orders
	else
	{

		// if done the rest, player can play a card order

	}

	// /*
	// 	Advance orders
	// */

	// // Advance to defend
	// for (auto territory1 : territoriesToDefend)
	// {
	// 	for (auto territory2 : territoriesToDefend)
	// 	{
	// 		if (territory1->territoryName.compare(territory2->territoryName) != 0)
	// 		{
	// 			std::cout << "Advance units from " << territory1->territoryName << " to " << territory2->territoryName << "? (y/n)" << std::endl;
	// 			string answer;
	// 			std::cin >> answer;
	// 			if (answer.compare("y") == 0)
	// 			{
	// 				std::cout << "How many units? " << std::endl;
	// 				string units;
	// 				std::cin >> units;

	// 				Advance *advance = new Advance(this, std::stoi(units), territory1, territory2);
	// 				this->issueOrder(advance);
	// 				break;
	// 			}
	// 		}
	// 	}
	// }

	// // Advance to attack
	// for (auto territory1 : territoriesToDefend)
	// {
	// 	for (auto territory2 : territoriesToAttack)
	// 	{
	// 		if (territory1->territoryName.compare(territory2->territoryName) != 0)
	// 		{
	// 			std::cout << "Advance units from " << territory1->territoryName << " to " << territory2->territoryName << "? (y/n)" << std::endl;
	// 			string answer;
	// 			std::cin >> answer;
	// 			if (answer.compare("y") == 0)
	// 			{
	// 				std::cout << "How many units? " << std::endl;
	// 				string units;
	// 				std::cin >> units;

	// 				Advance *advance = new Advance(this, std::stoi(units), territory1, territory2);
	// 				this->issueOrder(advance);
	// 				break;
	// 			}
	// 		}
	// 	}
	// }

	// /*
	// 	Issue order from one card in hand
	// */
	// for (auto card : this->getHand()->returnMyCards())
	// {
	// 	string cardType = "";

	// 	if (dynamic_cast<Card_Airlift *>(card) != nullptr)
	// 	{
	// 		cardType = "an Airlift";
	// 	}
	// 	else if (dynamic_cast<Card_Blockade *>(card) != nullptr)
	// 	{
	// 		cardType = "a Blockade";
	// 	}
	// 	else if (dynamic_cast<Card_Bomb *>(card) != nullptr)
	// 	{
	// 		cardType = "a Bomb";
	// 	}
	// 	else if (dynamic_cast<Card_Diplomacy *>(card) != nullptr)
	// 	{
	// 		cardType = "a Diplomacy";
	// 	}
	// 	else
	// 	{
	// 		cardType = "a Reinforcement";
	// 	}

	// 	std::cout << "Play " << cardType << "card? (y/n)" << std::endl;
	// 	string answer;
	// 	std::cin >> answer;
	// 	if (answer.compare("y") == 0)
	// 	{
	// 		card->play();
	// 		break;
	// 	}
	// }
}

// Assignment operator overload
void Player::operator=(Player &player)
{
	cout << "Player assignment operator called." << endl;
	hand = player.hand;
	ordersList = player.ordersList;
	ownedTerritories = player.ownedTerritories;
}

// Method to update player army count across their territories
void Player::updateTotalPlayerArmyCount()
{
	int numOfTroops = 0;
	for (Territory *territory : ownedTerritories)
	{
		numOfTroops = numOfTroops + territory->numOfArmies;
	}
	totalPlayerArmy = numOfTroops;
}

// Method to get player army count across their territories
int Player::getTotalPlayerArmy()
{
	updateTotalPlayerArmyCount();
	return totalPlayerArmy;
}

bool Player::isPlayerAttacked()
{
	if (totalPlayerArmy > getTotalPlayerArmy()) // Compare army before and army after update
	{
		return false;
	}
	return true;
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
