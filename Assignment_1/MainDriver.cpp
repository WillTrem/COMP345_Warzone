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

#include "CommandProcessing.h"

using namespace std;


int main()
{
	cout << "Hello CMake.\n"
		 << endl;

	// Assignment 1.
	
	// PART 1 test (shawn 40213581)
	//testLoadMap();

	// PART 2 test
	//testPlayers();

	// PART 3 test (chris)
	//testOrdersLists();

	// PART 4 test (Roxane)
	//testCards();

	// PART 5 test
	//testGameEngine();


	// Assignment 2.

	// PART 1 test

	CommandProcessor processorTest = CommandProcessor();
	Command* commandTest = processorTest.getCommand();
	cout << *commandTest;



	// Don't exit unless prompted.
	cout << "\n\nPress Enter to exit...";
	cin.get();

	return 0;
};
