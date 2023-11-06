#pragma once

#include <sstream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <functional>

using namespace std;

/**
 * Represents the various states a game can be in at any point in time
*/
using namespace std;
enum GameState
{
	// Start states
	START,
	MAP_LOADED,
	MAP_VALIDATED,
	PLAYERS_ADDED,
	// Play states
	ASSIGN_REINFORCEMENTS,
	ISSUE_ORDERS,
	EXECUTE_ORDERS,
	WIN,
	END
};


/**
 * A command consists of:
 * 1. The command string that needs to be provided as input to run it
 * 2. The function that gets called when the command is entered
 * 3. The next state to transition into after command is ran
*/
class Command
{
public:
	std::string cmdName;
	std::string parameter;
	void (*action)();
	GameState* nextState;
	string effect;

	//Constructor
	Command(std::string cmdName);
	Command(std::string cmdName, std::string parameter);
	Command(std::string* cmdName, void (*action)(), GameState* nextState);
	Command(const Command& command);

	// Saves the effect of the command after execution
	void saveEffect(string effect);

};


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