// PART 2.
// 
// Implement a group of C++ classes that implement a Warzone player. 
// Written by William Tremblay, 40174212.

#include "Cards.h"

class Player {
	private: 
	// TODO: Declare collection of Territories 
	// TODO: Declare list of orders
	Hand hand;

	public:
	// TODO: Declare toDefend()
	// TODO: Declare toAttack()
	// TODO: Declare issueOrder()

	Player();

	// TODO: Add territories to the constructor's parameters
	Player(Hand* initialHand);

	Hand getHand();
	



};