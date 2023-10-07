// MainDriver.cpp : Defines the entry point for the application.
//
// TEAM MEMBERS:
// Roxane Morin 40191881
// Evan Greenstein 40173229
// William Tremblay 40174212
// Chris Anglin 40216346
// Shawn 40213581

#include "MainDriver.h"
#include "CardsDriver.h"
#include "GameEngineDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "MapDriver.h"

using namespace std;

int main()
{
	cout << "Hello CMake.\n"
		 << endl;

	// Part 4 test (Roxane.)
	testCards();

	testPlayers();

	// PART 1 test (shawn 40213581)
	testLoadMap();

	// PART 3 test (chris)
	testOrdersLists();

	testGameEngine();

	return 0;
};
