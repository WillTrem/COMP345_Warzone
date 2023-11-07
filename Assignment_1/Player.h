// PART 2.
// 
// Implement a group of C++ classes that implement a Warzone player. 
// Written by William Tremblay, 40174212.

#include <string>

#include "Cards.h"
#include "Orders.h"
#include "Map.h"

using namespace std;
class Player {
	private: 
	vector<Territory*> ownedTerritories;
	OrdersList* ordersList = nullptr;
	Hand* hand = nullptr;
	string playerName;


	public:
	// Default constructor
	Player();

	// Parametrized constructors
	Player(string name);
	Player(Hand* initialHand, vector<Territory*> &initialTerritories, string name = "Player");

	// Copy constructor
	Player(const Player& player);

	// Destructor
	~ Player();


	// Getters and setters.
	Hand* getHand();

	vector<Territory*> getOwnedTerritories();
	void addOwnedTerritory(Territory* territory);
	Territory* removeOwnedTerritory(Territory* territory);

	OrdersList* getOrdersList();

	string getPlayerName();


	vector<Territory*> toDefend();

	vector<Territory*> toAttack();

	void issueOrder();
	
	// Assignment operator overload
	void operator=(Player& player);

	// Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream &out, const Player &p);
};


