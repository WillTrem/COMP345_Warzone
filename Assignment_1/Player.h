// PART 2.
// 
// Implement a group of C++ classes that implement a Warzone player. 
// Written by William Tremblay, 40174212.

#include "Cards.h"
#include "Orders.h"

class Player {
	private: 
	// TODO: Declare collection of Territories 
	OrdersList* ordersList;
	Hand* hand;

	public:
	// TODO: Declare toDefend()
	// TODO: Declare toAttack()

	// Default constructor
	Player();

	// TODO: Add territories to the constructor's parameters
	Player(Hand* initialHand);

	// Copy constructor
	Player(Player* player);

	Hand* getHand();

	OrdersList* getOrdersList();

	void issueOrder();
	
	void operator=(Player* player);
};