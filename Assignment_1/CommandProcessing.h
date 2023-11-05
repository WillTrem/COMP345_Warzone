#pragma once

#include "GameEngine.h"

using namespace std;
class CommandProcessor{
	
	private:
	// List of commands to execute
	vector<Command*> commandList;
	
	//Default Constructor
	CommandProcessor();

	//Copy Constructor
	CommandProcessor(const CommandProcessor& other);

	//Destructor
	~CommandProcessor();
	
	// Reads command input from user via console
	Command* readCommand();

	//Saves command to the list of
	void saveCommand(Command* command);

	public:
	// Gets a command from the user
	Command* getCommand();

	// Validates if a command is valid in the current game state;
	bool validate(Command* command, GameState currentState);

	// Assignment operator
	CommandProcessor& operator=(const CommandProcessor& other);

	// Stream Insertion Operator
	friend ostream& operator<<(ostream& os, const CommandProcessor& commandProcessor);

	static const map<string, list<GameState>> stateTransitions;
};