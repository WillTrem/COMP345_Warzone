#include "CommandProcessing.h"
#include "GameEngine.h"

#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

// Definition of stateTransitions (for validation)
std::map<std::string, std::vector<GameState>> stateTransitions = {
	{"loadmap", {START, MAP_LOADED}},
	{"validatemap", {MAP_LOADED}},
	{"addplayer", {MAP_VALIDATED, PLAYERS_ADDED}},
	{"gamestart", {PLAYERS_ADDED}},
	{"replay", {WIN}},
	{"quit", {WIN}},
	{"tournament", {START}}};

// Definition of commandTransitions
std::map<std::string, GameState> commandTransitions = {
	{"loadmap", MAP_LOADED},
	{"validatemap", MAP_VALIDATED},
	{"addplayer", PLAYERS_ADDED},
	{"gamestart", ASSIGN_REINFORCEMENTS},
	{"replay", START},
	{"quit", END},
	{"tournament", ASSIGN_REINFORCEMENTS}};

// Constructor with only command name
Command::Command(std::string cmdName) : cmdName(cmdName) {}

// Constructor with with both command name and parameter
Command::Command(std::string cmdName, std::string parameter) : cmdName(cmdName), parameter(parameter) {}

/**
 * Normal constructor
 */
Command::Command(std::string *cmdName, void (*action)(), GameState *nextState) : cmdName(*cmdName),
																				 action(action),
																				 nextState(nextState) {}
/**
 * Copy constructor
 */
Command::Command(const Command &command) : cmdName(command.cmdName),
										   action(command.action),
										   nextState(command.nextState) {}

// Save the command's effect to a string; called upon its execution.
void Command::saveEffect(string effectString = "A command did a thing.")
{
	effect = new string(effectString);
	Notify(*this);
}

string Command::stringToLog() const
{
	return "Command Log: Effect Saved - " + *this->effect;
}

// Executive functions used by commands.

// Load the map with the name stored in the command's 'parameter' param.
// The map is loaded in the passed gameEngine's "gameMap" param, given by reference.
bool Command::loadMap(GameState *&gameState, Map *&gameMap, std::vector<Player *> *&gamePlayers, Deck *&gameDeck)
{
	gameMap = new Map();
	gameMap->loadMap(parameter);

	cout << "\nSuccessfully loaded map " << gameMap->mapName << "." << endl;
	cout << "Available commands: 'loadmap' , 'validatemap'.\n\n"
		 << endl;

	saveEffect("Successfully loaded map " + gameMap->mapName + ".");

	gameState = nextState;
	return true;
}

// Validate the currently loaded map.
// The map is stored in the passed gameEngine's "gameMap" param, given by reference.
bool Command::validateMap(GameState *&gameState, Map *&gameMap, std::vector<Player *> *&gamePlayers, Deck *&gameDeck)
{
	gameMap->validate();

	cout << "\nSuccessfully validated map " << gameMap->mapName << "." << endl;
	cout << "Available commands : 'addplayer'.\n\n"
		 << endl;

	saveEffect("Successfully validatedF map " + gameMap->mapName + ".");

	gameState = nextState;
	return true;
}

// Add player to the current game set up.
// Players are stored in the passed gameEngine's "players" param, given by reference.
bool Command::addPlayer(GameState *&gameState, Map *&gameMap, std::vector<Player *> *&gamePlayers, Deck *&gameDeck)
{
	if (gamePlayers->size() < 6)
	{
		Player *newPlayer = new Player(parameter);
		gamePlayers->push_back(newPlayer);

		cout << "New player " << newPlayer->getPlayerName() << " has beed added to the game." << endl;
		cout << "Available commands: 'addplayer' , 'gamestart'.\n\n"
			 << endl;

		saveEffect("New player " + newPlayer->getPlayerName() + " has beed added to the game.");

		gameState = nextState;
		return true;
	}
	else
	{
		cout << "The game is full; additional players may not be added.\n"
			 << endl;
		return false;
	}
}

// Divide the map's territories among players, determine play order, give players cards and starting units.
// The various objects involved are passed as references from a GameEngine class.
bool Command::gameStart(GameState *&gameState, Map *&gameMap, std::vector<Player *> *&gamePlayers, Deck *&gameDeck)
{
	if (gamePlayers->size() > 1)
	{
		cout << "Preparing to begin the game...\n\n"
			 << endl;

		// Fairly distribute all the territories to the players.
		// What to do if they cannot be evenly divided?
		int numPlayers = gamePlayers->size();
		int numTerritories = gameMap->mapTerritories.size();

		for (int i = 0; i < numTerritories; i++)
		{
			int playerIndex = i % numPlayers;

			// Assign the territory at gameMap->mapTerritories[i] to the player at players[playerIndex].
			gamePlayers->at(playerIndex)->addOwnedTerritory(gameMap->mapTerritories.at(i));
			gameMap->mapTerritories.at(i)->occupierName = gamePlayers->at(playerIndex)->getPlayerName();

			cout << "Assigned territory " << gameMap->mapTerritories.at(i)->territoryName << " to player " << gamePlayers->at(playerIndex)->getPlayerName() << ".\n"
				 << endl;
		}

		// Determine randomly the order of play of the players in the game.
		std::random_device randomizer;
		std::mt19937 twister(randomizer());
		std::shuffle(gamePlayers->begin(), gamePlayers->end(), twister); // Shuffle the players vector so they won't necessarily go in their input order.

		// Doing both steps C and D in the same loop for efficiency's sake.
		for (int i = 0; i < numPlayers; i++)
		{
			// Give 50 initial army units to the players, which are placed in their respective reinforcement pool.
			gamePlayers->at(i)->setReinforcementPool(gamePlayers->at(i)->getReinforcmentPool() + 50);
			cout << "\n\nAwarded 50 reinforcement units to player " << gamePlayers->at(i)->getPlayerName() << ".\nThey will now draw cards."
				 << endl;

			// Let each player draw 2 initial cards from the deck using the deck's draw() method.
			Hand *currentHand = gamePlayers->at(i)->getHand();
			gameDeck->draw(currentHand);
			gameDeck->draw(currentHand);
		}

		// switch the game to the play phase
		cout << "\n\nStartUp phase completed. The game will now begin.\n"
			 << endl;

		saveEffect("The start up phase has been completed; territories and cards have been distributed.\nThe game will now begin.");

		gameState = nextState;
		return true;
	}
	if (gamePlayers->size() == 1)
	{
		std::cout << "Please add at least one more player before starting the game.\n"
				  << std::endl;
		return false;
	}
}

// Starts a tournament based on the command parameters given 
bool Command::toggleTournamentMode(GameState *&gameState, Map *&gameMap, std::vector<Player *> *&gamePlayers, Deck *&gameDeck)
{
	string token;

	istringstream iss(parameter);
	string option = "";
	vector<string> values;
	int numMaps = -1;
	Tournament* tournament = new Tournament();
	tournament->gameEngine = this->gameEngine;

	// Ensures all options have been used in the command
	int optionsCounter[4] = {0, 0, 0, 0};
	
	while (getline(iss, token, ' '))
	{
		bool isOption = token.compare("-M") == 0 ||
						token.compare("-P") == 0 ||
						token.compare("-G") == 0 ||
						token.compare("-D") == 0;
		if (option.empty() && isOption)
		{
			option = token;
		}
		else if (!option.empty() && !isOption)
		{
			values.push_back(token);
		}
		else if (!option.empty() && isOption)
		{
			/*
				Maps per game option
			*/
			if (option.compare("-M") == 0)
			{
				optionsCounter[0]++;
				numMaps = values.size();
				if (numMaps >= 1 && numMaps <= 5)
				{
					// TODO: load maps into
					for(auto map : values)
					{
						Map* newMap = new Map();
						newMap->loadMap(map);
						tournament->addMap(newMap);
					}
				}
				else
				{
					std::cout << "Invalid number of maps (1-5 inclusive)\n"
							  << std::endl;
					return false;
				}
			}
			/*
				Player players option
			*/
			else if (option.compare("-P") == 0)
			{
				optionsCounter[1]++;
				if (values.size() >= 2 && values.size() <= 4)
				{
					// Verifying for duplicate players 
					unordered_set<string> uniqueValues(values.begin(), values.end());
					if (uniqueValues.size() != values.size())
					{
						std::cout << "Duplicate players strategies detected. Only put in different strategies.\n"
								  << std::endl;
						return false;
					}

					// Parsing the players
					for(auto strategy : values)
					{
						PlayerStrategy* newStrategy = nullptr;
						Player* newPlayer = new Player(strategy);
						if(strategy.compare("aggressive") == 0)
						{
							newStrategy = new AggressivePlayerStrategy(newPlayer);							
						}
						else if(strategy.compare("benevolent") == 0)
						{
							newStrategy = new BenevolentPlayerStrategy(newPlayer);
						}
						else if(strategy.compare("random") == 0)
						{
							newStrategy = new NeutralPlayerStrategy(newPlayer);
						}
						else if(strategy.compare("cheater") == 0)
						{
							newStrategy = new CheaterPlayerStrategy(newPlayer);
						}
						else
						{
							std::cout << "Invalid strategy\n"
									  << std::endl;
							return false;
						}
						newPlayer->setStrategy(newStrategy);
						tournament->addPlayer(newPlayer);
					}

				}
				else
				{
					std::cout << "Invalid number of player players (2-4 inclusive)\n"
							  << std::endl;
					return false;
				}

			}
			/*
				Number of games option
			*/
			else if (option.compare("-G") == 0)
			{
				optionsCounter[2]++;
				if (values.size() == 1)
				{
					try
					{
						int numGames = std::stoi(values[0]);
						if (numGames >= 1 && numGames <= 5)
						{
							tournament->setNumberOfGames(numGames);
						}
						else
						{
							std::cout << "Invalid number of turns (between 1-5 inclusive)\n"
									  << std::endl;
							return false;
						}
					}
					catch (const std::exception &e)
					{
						std::cout << e.what() << std::endl
								  << std::endl;
						return false;
					}
				}
				else
				{
					std::cout << "Games option only takes 1 number\n"
							  << std::endl;
					return false;
				}
			}
			/*
				Number of turns for each game option
			*/
			else if (option.compare("-D") == 0){
				optionsCounter[3]++;
				if (values.size() == 1)
				{
					try
					{
						int numTurns = std::stoi(values[0]);
						if (numTurns >= 10 && numTurns <= 50)
						{
							tournament->setMaxTurns(numTurns);
						}
						else
						{
							std::cout << "Invalid number of turns (between 10-50 inclusive)\n"
									  << std::endl;
							return false;
						}
					}
					catch (const std::exception &e)
					{
						std::cout << e.what() << std::endl
								  << std::endl;
						return false;
					}
				}
				else
				{
					std::cout << "Turns option only takes 1 number (same amount of turns for each game)\n"
							  << std::endl;
					return false;
				}
			}
			

			option = token;
			values = {};
		}
	}

	// Ensuring all options have been called
	for(auto option : optionsCounter)
	{
		if(option != 1)
		{
			std::cout << "All options must be called only once\n"
					  << std::endl;
			return false;
		}
	}

	gameState = nextState;
	// Start the tournament
	tournament->play();
	return true;
}

//-------------------- COMMAND PROCESSOR --------------------

// Default Constructor
CommandProcessor::CommandProcessor()
{
	commandList = {};
};

// Copy Constructor
CommandProcessor::CommandProcessor(const CommandProcessor &other)
{
	commandList = other.commandList;
};

// Destructor
CommandProcessor::~CommandProcessor()
{
	commandList.clear();
};

// Reads the command from the user via console
Command *CommandProcessor::readCommand()
{
	string input;
	cout << "Enter a command: ";
	getline(cin, input);
	cout << endl;

	// split the input string into a vector of strings
	vector<string> inputCommand;
	string token;

	istringstream iss(input);
	bool commandNameRetrived = false;
	string options = "";
	while (getline(iss, token, ' '))
	{
		if (!commandNameRetrived)
		{
			inputCommand.push_back(token);
			commandNameRetrived = true;
		}
		else
		{
			options.append(token + " ");
		}
	}
	inputCommand.push_back(options);

	// Calling the corresponding constructor based on the number of parameters
	Command *newCommand = (inputCommand.size() == 1) ? new Command(inputCommand[0]) : new Command(inputCommand[0], inputCommand[1]);
	
	// Passing down the reference of the gameEngine to the command
	newCommand->gameEngine = this->gameEngine;
	
	return newCommand;
};

string CommandProcessor::stringToLog() const
{
	return "Command Processor Log: Command Saved - " + this->commandList.back()->cmdName;
}

// Saves the command in the list of commands
void CommandProcessor::saveCommand(Command *command)
{
	commandList.push_back(command);
	Notify(*this); // Notify Subject
};

// Gets a command from the user
Command *CommandProcessor::getCommand()
{
	Command *command = readCommand();
	saveCommand(command);
	return command;
};

// Verifies if a command is valid in the current game state
bool CommandProcessor::validate(Command *command, GameState currentState)
{
	// Is this a known command?
	if (stateTransitions.find(command->cmdName) == stateTransitions.end())
	{
		cout << command->cmdName << " is not a recognized command." << endl;
		return false;
	}
	else
	{
		for (auto &state : stateTransitions.at(command->cmdName))
		{
			if (state == currentState)
			{
				// Assign valid commands their transitions states, potentially actions.
				setUpCommand(command);
				return true;
			}
		}

		string errorMessage = "Command \"" + command->cmdName + "\" is invalid for the current game state.";
		cout << errorMessage << endl;
		// Sets the effect of the command to an error message
		command->effect = new string(errorMessage);

		return false;
	}
};

// Set a command's nextState and Action according to its type.
void CommandProcessor::setUpCommand(Command *command)
{
	// We assume the command is already valid, as this function is called from inside the validate one.

	GameState *nextState = new GameState(commandTransitions.at(command->cmdName));
	command->nextState = nextState;

	// Set up the command's corresponding action function.
	if (command->cmdName == "loadmap")
		command->execution = &Command::loadMap;
	if (command->cmdName == "validatemap")
		command->execution = &Command::validateMap;
	if (command->cmdName == "addplayer")
		command->execution = &Command::addPlayer;
	if (command->cmdName == "gamestart")
		command->execution = &Command::gameStart;
	if (command->cmdName == "tournament")
		command->execution = &Command::toggleTournamentMode;
	

	// cout << "\nDone setting up the command \"" << command->cmdName << "\".\n" << endl;
};

// Assignment operator
CommandProcessor &CommandProcessor::operator=(const CommandProcessor &other)
{
	commandList = other.commandList;
	return *this;
};

// Stream Insertion Operator
ostream &operator<<(ostream &os, const CommandProcessor &commandProcessor)
{
	for (auto &command : commandProcessor.commandList)
	{
		os << command->cmdName << " " << command->parameter << endl;
	}
	return os;
};

// ------------------- FILE COMMAND PROCESSOR ADAPTER -------------------

// Parametrized Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string fileName)
{
	fileLineReader = new FileLineReader(fileName);
};

// Copy Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &other)
{
	fileLineReader = new FileLineReader(other.fileLineReader->getFileName());
};

// Destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
	delete fileLineReader;
	fileLineReader = NULL;
};

// Reads the command from a line of the file
Command *FileCommandProcessorAdapter::readCommand()
{
	string input = fileLineReader->readLineFromFile();

	// split the input string into a vector of strings
	vector<string> inputCommand;
	string token;

	istringstream iss(input);
	while (getline(iss, token, ' '))
	{
		inputCommand.push_back(token);
	}

	// Calling the corresponding constructor based on the number of parameters
	Command *newCommand = (inputCommand.size() == 1) ? new Command(inputCommand[0]) : new Command(inputCommand[0], inputCommand[1]);
	
	// Passing down the reference of the gameEngine to the command
	newCommand->gameEngine = this->gameEngine;

	return newCommand;
};

// Assignment Operator
FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &other)
{
	fileLineReader = new FileLineReader(other.fileLineReader->getFileName());
	return *this;
};

// Stream Insertion Operator
ostream &operator<<(ostream &os, const FileCommandProcessorAdapter &commandProcessor)
{
	for (auto &command : commandProcessor.commandList)
	{
		os << command->cmdName << " " << command->parameter << endl;
	}
	return os;
};

// -----------------FILE LINE READER-----------------
// Parametrized Constructor
FileLineReader::FileLineReader(string fileName)
{
	fileName = fileName;
	fileStream = new ifstream(fileName);
}

// Copy Constructor
FileLineReader::FileLineReader(const FileLineReader &other)
{
	fileName = other.fileName;
	fileStream = new ifstream(other.fileName);
}

// Destructor
FileLineReader::~FileLineReader()
{
	delete fileStream;
	fileStream = NULL;
}

// Assignment operator
FileLineReader &FileLineReader::operator=(const FileLineReader &other)
{
	fileName = other.fileName;
	fileStream = new ifstream(other.fileName);
	return *this;
}

// Stream Insertion Operator
ostream &operator<<(ostream &os, const FileLineReader &fileLineReader)
{
	os << fileLineReader.fileName << endl;
	return os;
}

// Returns the file name
string FileLineReader::getFileName()
{
	return fileName;
}

// Reads a line from the file
string FileLineReader::readLineFromFile()
{
	string input;
	getline(*fileStream, input);
	return input;
}