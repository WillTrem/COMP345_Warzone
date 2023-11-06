#include "CommandProcessing.h"

#include <sstream>
#include <fstream>

using namespace std;


// Constructor with only command name
Command::Command(std::string cmdName) : cmdName(cmdName) {}

//Constructor with with both command name and parameter
Command::Command(std::string cmdName, std::string parameter) : cmdName(cmdName), parameter(parameter) {}


/**
 * Normal constructor
*/
Command::Command(std::string* cmdName, void (*action)(), GameState* nextState) :
	cmdName(*cmdName),
	action(action),
	nextState(nextState) {}

/**
 * Copy constructor
*/
Command::Command(const Command& command) :
	cmdName(command.cmdName),
	action(command.action),
	nextState(command.nextState) {}


const map<string, list<GameState>> CommandProcessor::stateTransitions = {
        {"loadmap",{
			START, 
			MAP_LOADED
			}},
		{"validatemap", {
			MAP_LOADED
			}},
		{"addplayer", {
			MAP_VALIDATED, 
			PLAYERS_ADDED
			}},
		{"gamestart", {
			PLAYERS_ADDED
			}},
		{"replay", {
			WIN
			}},
		{"quit", {
			WIN
		}}
	};

// Default Constructor
CommandProcessor::CommandProcessor(){
	commandList = {};
};

// Copy Constructor
CommandProcessor::CommandProcessor(const CommandProcessor& other){
	commandList = other.commandList;
};

// Destructor
CommandProcessor::~CommandProcessor(){
	commandList.clear();
};

// Reads the command from the user via console
Command* CommandProcessor::readCommand(){
	string input;
	cout<<"Enter a command: ";
	getline(cin, input);
	cout<<endl;

	//split the input string into a vector of strings
	vector<string> inputCommand;
	string token;

	istringstream iss(input);
	while(getline(iss, token, ' ')){
		inputCommand.push_back(token);
	}
	
	// Calling the corresponding constructor based on the number of parameters
	Command* newCommand = (inputCommand.size() == 1) ? new Command(inputCommand[0]) : new Command(inputCommand[0], inputCommand[1]);
	return newCommand;
};

// Saves the command in the list of commands
void CommandProcessor::saveCommand(Command* command){
	commandList.push_back(command);
};

// Gets a command from the user
Command* CommandProcessor::getCommand(){
	Command* command = readCommand();
	saveCommand(command);
	return command;
};

// Verifies if a command is valid in the current game state
bool CommandProcessor::validate(Command* command, GameState currentState){
	for(auto& state : stateTransitions.at(command->cmdName)){
		if(state == currentState){
			return true;
		}
	}
	
	string errorMessage = "Command \"" + command->cmdName + "\" is invalid for the current game state.";
	cout<<errorMessage<<endl;
	// Sets the effect of the command to an error message
	command->effect = errorMessage;
	return false;
};

// Assignment operator
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& other){
	commandList = other.commandList;
	return *this;
};

// Stream Insertion Operator
ostream& operator<<(ostream& os, const CommandProcessor& commandProcessor){
	for(auto& command : commandProcessor.commandList){
		os<<command->cmdName<<" "<<command->parameter<<endl;
	}
	return os;
};

// Parametrized Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string fileName): fileName(fileName){
	fileStream = new ifstream(fileName);
};

// Copy Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other){
	fileStream = new ifstream(other.fileName);
};

// Destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
	delete fileStream;
	fileStream = NULL;
};

// Reads the command from a line of the file
Command* FileCommandProcessorAdapter::readCommand(){
	string input;
	getline(*fileStream, input);

	//split the input string into a vector of strings
	vector<string> inputCommand;
	string token;

	istringstream iss(input);
	while(getline(iss, token, ' ')){
		inputCommand.push_back(token);
	}

	//Calling the corresponding constructor based on the number of parameters
	Command* newCommand = (inputCommand.size() == 1) ? new Command(inputCommand[0]) : new Command(inputCommand[0], inputCommand[1]);
	return newCommand;
};

// Assignment Operator
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& other){
	fileStream = new ifstream(other.fileName);
	return *this;
};

// Stream Insertion Operator
ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& commandProcessor){
	for(auto& command : commandProcessor.commandList){
		os<<command->cmdName<<" "<<command->parameter<<endl;
	}
	return os;
};
