﻿// MainDriver.cpp : Defines the entry point for the application.
//
// TEAM MEMBERS:
// Roxane Morin 40191881
// Evan Greenstein 40173229
// William Tremblay 40174212
// Chris Anglin 40216346
// Shawn 40213581

#include "MainDriver.h"

using namespace std;

int main(int argc, char *argv[])
{
	
	// Assignment 1.

	// PART 1 test (shawn 40213581)
	// testLoadMap();

	// Part 2 test
	// testPlayers();

	// PART 3 test (chris)
	// testOrdersLists();

	// Part 4 test (Roxane.)
	// testCards();

	// Part 5 test
	// testGameEngine();
	
	
	// Assignment 2.	

	// // Parsing arguments
	// CommandProcessor *commandProcessor = nullptr;

	// if (argc == 2 && argv[0] == "-file")
	// {
	// 	try
	// 	{
	// 		cout << "Using file " << argv[1] << " as input source for commands." << endl;
	// 		commandProcessor = new FileCommandProcessorAdapter(argv[1]);
	// 	}
	// 	catch (exception e)
	// 	{
	// 		cout << "An error occured while reading the file " << argv[1] << ". Defaulting to using console mode" << endl;
	// 	};
	// }
	// else
	// {
	// 	cout << "Using console as input source for commands." << endl;
	// 	commandProcessor = new CommandProcessor();
	// }

	// testCommandProcessor();

	// Part 2 (StartUp Phase) Test.
	// testStartupPhase();

	// testMainGameLoop();

	// testOrderExecution();

	// testLoggingObserver();

	
	// Assignment 3.	

	//testPlayerStrategies();

	// this test function just creates a new GameEngine with the tournament constructor
	// tournament mode can be tested by passing in a tournament command to the commandprocessor:
    // tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>
	testTournament();

	

	return 0;
};
