#pragma once

#include "Cards.h"

#include <iostream>
using namespace std;

// Placeholders for classes that need to be referenced, but don't yet exist.
// To update/delete once those have been implemented.

class Player
{
public:
	Hand* myHand;

	Player(Hand* hand) 
	{
		myHand = hand;
	};
};