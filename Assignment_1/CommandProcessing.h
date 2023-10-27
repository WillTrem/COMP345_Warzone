#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <map>

//#include "GameEngine.h"

// PART 1.
// 
// Implement a CommandProcessor class, a FileCommandProcessorAdapter class.
// All the classes / functions that you implement for this component must all reside in a single.cpp / .h file duo named CommandProcessing.cpp / CommandProcessing.h.

// Written by Roxane Morin, 40191881.

//const multimap<string, GameState> CommandValidityByState =
//{
//	{"loadmap", GameState::START}, // Will need to trunkcate away the '<mapfile>' part of the string.
//	{"loadmap", GameState::MAP_LOADED},
//	{"validatemap", GameState::MAP_LOADED},
//	{"addplayer", GameState::MAP_VALIDATED},
//	{"addplayer", GameState::PLAYERS_ADDED},
//	{"gamestart", GameState::PLAYERS_ADDED},
//	{"replay", GameState::WIN},
//	{"quit", GameState::WIN}
//};


using namespace std;

class Command
{
private:
	// Variables
	string* myInputString = nullptr;
	string* myEffect = nullptr;

public:
	// Constructors & destructor.
	Command(string& inputString);
	Command(); // Parameter-free constructor just in case.
	~Command();

	// Methods
	void saveEffect(string* effectString);

	// Overloads
	void operator=(Command& Command);
	friend ostream& operator<<(ostream& out, const Command& command);
};

class CommandProcessor
{
private:
	// Variables
	stack<Command*> commands;

	// Methods
	void readCommand();
	void saveCommand(string inputString);

public:
	// Constructor
	CommandProcessor();

	// Methods
	Command* getCommand();
	//bool validate();

};

