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

using namespace std;

int main()
{
	cout << "Hello CMake.\n"
		 << endl;

	// Roxane's testing area.
	testCards();

	testPlayers();

	// PART 3 test (chris)
	testOrdersLists();

	testGameEngine();

	return 0;
};
