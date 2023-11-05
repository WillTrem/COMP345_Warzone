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

int main(int argc, char* argv[])
{
	// Parsing arguments
	CommandProcessor* commandProcessor = nullptr;

	if(argc == 2 && argv[0] == "-file"){
		try{
			commandProcessor = new FileCommandProcessorAdapter(argv[1]);
			cout<<"Using file "<<argv[1]<<" as input source for commands."<<endl;
		} 
		catch(exception e){
			cout<<"An error occured while reading the file "<< argv[1]<<". Defaulting to using console mode"<<endl;
		};
	}else{
		commandProcessor = new CommandProcessor();
		cout<<"Using console as input source for commands."<<endl;
	}

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
