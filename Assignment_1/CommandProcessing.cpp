#include "CommandProcessing.h"
#include "GameEngine.h"

#include <sstream>

using namespace std;

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
	//TODO implement Command constructor with command parameter as string
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

	//Calling the corresponding constructor based on the number of parameters
	Command* newCommand = (inputCommand.size() == 1) ? new Command(&inputCommand[0]) : new Command(&inputCommand[0], inputCommand[1]);
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
	for(auto& state : stateTransitions.at(*command->cmdName)){
		if(state == currentState){
			return true;
		}
	}
	string errorMessage = "Command \"" + *command->cmdName + "\" invalid for the current game state.";
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
		os<<*command->cmdName<<" "<<command->parameter<<endl;
	}
	return os;
};
