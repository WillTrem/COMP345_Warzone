// PART 2.
// 
// Implement a group of C++ classes that implement a Warzone player. 
// Written by William Tremblay, 40174212.

#include "Cards.h"
#include "Orders.h"
#include "Map.h"

using namespace std;
class Player {
	private: 
	vector<Territory *> ownedTerritories;
	OrdersList* ordersList = nullptr;
	Hand* hand = nullptr;

	public:

	// Default constructor
	Player();

	// Parametrized constructor
	Player(Hand* initialHand, vector<Territory*> &initialTerritories);

	// Copy constructor
	Player(Player& player);

	// Destructor
	~ Player();

	Hand* getHand();

	vector<Territory*> getOwnedTerritories();

	OrdersList* getOrdersList();

	vector<Territory*> toDefend();

	vector<Territory*> toAttack();

	void issueOrder();
	
	// Assignment operator overload
	void operator=(Player& player);

	// Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream &out, const Player &p);
};


