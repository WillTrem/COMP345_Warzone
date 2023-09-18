// PART 2.
// 
// Implement a group of C++ classes that implement a Warzone player. 
// Written by William Tremblay, 40174212.

#include "Player.h"
#include "Cards.h"

// Warzone player
Player::Player(){
	hand = Hand();
}

// Warzone player
Player::Player(Hand* initialHand){
	hand = *initialHand;
}

// Returns the hand of the player
Hand Player::getHand(){
	return hand;
}

// TODO: Implement toDefend()
// TODO: Implement toAttack()
// TODO: Implement issueOrder()