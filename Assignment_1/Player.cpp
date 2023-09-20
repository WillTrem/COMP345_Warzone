// PART 2.
// 
// Implement a group of C++ classes that implement a Warzone player. 
// Written by William Tremblay, 40174212.

#include "Player.h"
#include "Cards.h"
#include "Orders.h"

// Default constructor
Player::Player(){
	hand = new Hand();
	ordersList = new OrdersList();
}

// Parametrized connstructor
Player::Player(Hand* initialHand){
	hand = initialHand;
	ordersList = new OrdersList();
}

// Returns the hand of the player
Hand* Player::getHand(){
	return hand;
}

// Returns the player's current orders list
OrdersList* Player::getOrdersList(){
	return ordersList;
}

// TODO: Implement toDefend()
// TODO: Implement toAttack()
void Player::issueOrder(){
	Order* newOrder = new Order();

	ordersList->addOrder(newOrder);

	std::cout << "An order has been issued" << std::endl;
}