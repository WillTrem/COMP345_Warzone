#pragma once

#include "GameEngine.h"

#include <sstream>
#include <fstream>

using namespace std;
class CommandProcessor{
	protected:
	// List of commands to execute
	vector<Command*> commandList;
	
	private:
	
	// Reads command input from user via console
	virtual Command* readCommand();

	//Saves command to the list of
	void saveCommand(Command* command);

	public:
	//Default Constructor
	CommandProcessor();

	//Copy Constructor
	CommandProcessor(const CommandProcessor& other);

	//Destructor
	~CommandProcessor();
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


class FileCommandProcessorAdapter : public CommandProcessor{
	private:
	ifstream* fileStream = nullptr;	
	Command* readCommand(); 

	public:
	string fileName;
	//Parametrized Constructor
	FileCommandProcessorAdapter(string fileName);

	// Copy Constructor
	FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);

	// Destructor
	~FileCommandProcessorAdapter();
	

	// Assignment operator
	FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& other);

	// Stream Insertion Operator
	friend ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& commandProcessor);

};