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

// Parametrized constructor
Player::Player(Hand* initialHand){
	hand = initialHand;
	ordersList = new OrdersList();
}

Player::Player(Player* player){
	//TODO: Add Territories list
	hand = new Hand(player->hand);
	// ordersList = new OrdersList(player->ordersList); Waiting for copy constructor to be implemented
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

// Creates a new order and adds it to the player's list of current orders
void Player::issueOrder(){
	Order* newOrder = new Order();

	ordersList->addOrder(newOrder);

	std::cout << "An order has been issued" << std::endl;
}

// Assignment operator overload
void Player::operator=(Player* player){
	hand = player->hand;
	ordersList = player->ordersList;
	//TODO: add territories 
}