// Assignment_1.cpp : Defines the entry point for the application.
//

#include "Assignment_1.h"
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
