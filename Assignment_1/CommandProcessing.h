#pragma once
#pragma clang diagnostic ignored "-Wc++11-extensions"

#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "LogObserver.h"

#include <sstream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

/**
 * Represents the various states a game can be in at any point in time
 */
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
	END,
};

// Maps which state(s) a command is valid in.
extern std::map<std::string, std::vector<GameState> > stateTransitions;

// Maps which state(s) a command is valid in.
extern std::map<std::string, GameState> commandTransitions;

/**
 * A command consists of:
 * 1. The command string that needs to be provided as input to run it
 * 2. The function that gets called when the command is entered
 * 3. The next state to transition into after command is ran
 */
class Command : public Subject, public ILoggable
{
public:
	std::string cmdName;
	std::string parameter;
	void (*action)(); // Had to do a second version, otherwise it breaks the existing code.
	bool (Command::*execution)(GameState *&gameState, Map *&gameMap, std::vector<Player *> *&gamePlayers, Deck *&gameDeck);
	GameState *nextState;
	string *effect;

	// Constructor
	Command(std::string cmdName);
	Command(std::string cmdName, std::string parameter);
	Command(std::string *cmdName, void (*action)(), GameState *nextState);
	Command(const Command &command);

	// Saves the effect of the command after execution
	void saveEffect(string effectString);

	// Function to log to GameLog.txt
	string stringToLog() const override;

	// Executive functions used by commands.
	bool loadMap(GameState *&gameState, Map *&gameMap, std::vector<Player *> *&gamePlayers, Deck *&gameDeck);
	bool validateMap(GameState *&gameState, Map *&gameMap, std::vector<Player *> *&gamePlayers, Deck *&gameDeck);
	bool addPlayer(GameState *&gameState, Map *&gameMap, std::vector<Player *> *&gamePlayers, Deck *&gameDeck);
	bool gameStart(GameState *&gameState, Map *&gameMap, std::vector<Player *> *&gamePlayers, Deck *&gameDeck);
};

// Command processors.

class CommandProcessor : public Subject, public ILoggable
{
protected:
	// List of commands to execute
	vector<Command *> commandList;

private:
	// Reads command input from user via console
	virtual Command *readCommand();

	// Set a command's nextState and Action according to its type.
	void setUpCommand(Command *command);

public:
	// Default Constructor
	CommandProcessor();

	// Copy Constructor
	CommandProcessor(const CommandProcessor &other);

	// Destructor
	~CommandProcessor();
	// Gets a command from the user
	Command *getCommand();

	// Validates if a command is valid in the current game state;
	bool validate(Command *command, GameState currentState);

	// Function to log to GameLog.txt
	string stringToLog() const override;

	// Saves command to the list of
	void saveCommand(Command *command);

	// Assignment operator
	CommandProcessor &operator=(const CommandProcessor &other);

	// Stream Insertion Operator
	friend ostream &operator<<(ostream &os, const CommandProcessor &commandProcessor);

	// static const map<string, list<GameState>> stateTransitions; // Moved out of the class, now a free variable accessible to all.
};

class FileLineReader
{
private:
	ifstream *fileStream = nullptr;
	string fileName;

public:
	// Parametrized Constructor
	FileLineReader(string fileName);

	// Copy Constructor
	FileLineReader(const FileLineReader &other);

	// Destructor
	~FileLineReader();

	// Assignment operator
	FileLineReader &operator=(const FileLineReader &other);

	// Stream Insertion Operator
	friend ostream &operator<<(ostream &os, const FileLineReader &fileLineReader);

	// Returns the file name
	string getFileName();

	// Reads a line from the file
	string readLineFromFile();
};

// Adpater class between CommandProcessor and FileLineReader
class FileCommandProcessorAdapter : public CommandProcessor
{
private:
	FileLineReader *fileLineReader = nullptr;
	Command *readCommand();

public:
	// Parametrized Constructor
	FileCommandProcessorAdapter(string fileName);

	// Copy Constructor
	FileCommandProcessorAdapter(const FileCommandProcessorAdapter &other);

	// Destructor
	~FileCommandProcessorAdapter();

	// Assignment operator
	FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &other);

	// Stream Insertion Operator
	friend ostream &operator<<(ostream &os, const FileCommandProcessorAdapter &commandProcessor);
};
