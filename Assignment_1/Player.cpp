// PART 2.
//
// Implement a group of C++ classes that implement a Warzone player.
// Written by William Tremblay, 40174212.

#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

using namespace std;
// Default constructor
Player::Player()
{
	hand = new Hand();
	ownedTerritories = {new Territory(), new Territory(), new Territory()};
	ordersList = new OrdersList();

	playerName = "Player";
}

// Parametrized constructorw
Player::Player(string name)
{
	hand = new Hand();
	ownedTerritories = { new Territory(), new Territory(), new Territory() };
	ordersList = new OrdersList();

	playerName = name;
}
Player::Player(Hand *initialHand, vector<Territory*> &initialTerritories, string name)
{
	hand = initialHand;
	ownedTerritories = initialTerritories;
	ordersList = new OrdersList();

	playerName = name;
}

// Copy constructor
Player::Player(const Player &player)
{
	hand = new Hand(player.hand);
	ownedTerritories = vector<Territory*>(player.ownedTerritories);
	ordersList = new OrdersList(*player.ordersList); 

	playerName = *new string(player.playerName);
}

Player::~Player(){
	cout<<"Player destructor called"<<endl;

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
vector<Territory*> Player::getOwnedTerritories(){
	return ownedTerritories;
}

// Returns an arbitrary list of territories to attack
vector<Territory*> Player::toDefend(){
	return {new Territory(), new Territory(), new Territory()};
}

// Returns an arbitrary list of territories to attack
vector<Territory*> Player::toAttack(){
	return {new Territory(), new Territory(), new Territory()};
}

// Creates a new order and adds it to the player's list of current orders
void Player::issueOrder()
{
	Order *newOrder = new Order();

	ordersList->addOrder(newOrder);

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
