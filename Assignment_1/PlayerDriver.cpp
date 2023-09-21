// PART 2.
// 
// Implement a group of C++ classes that implement a Warzone player. 
// Written by William Tremblay, 40174212.
#pragma once
#include "Player.h"
#include "Cards.h"

using namespace std;
void testPlayers(){
	Player p1 = Player();
	Hand p2StartingHand = Hand();
	Player p2(&p2StartingHand);

	cout<<"P1 issuing order"<<endl;
	p1.issueOrder();
	cout<<"P1 next order: "<< p1.getOrdersList()->getNextOrder()<<endl;

	cout<<"P2 hand object: "<<p2.getHand()<<endl;

	//TODO: add copy constructor and assignment operator to driver
}
