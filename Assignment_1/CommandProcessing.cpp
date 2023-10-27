#pragma once

#include "CommandProcessing.h"

using namespace std;

// COMMAND
Command::Command(string& inputString)
{
	myInputString = new string(inputString);
	// Initially, we have no effect string.
};
Command::Command()
{
	myInputString = new string("[Empty command.]"); // Create an empty dummy string.
	// Initially, we have no effect string.
};

Command::~Command()
{
	cout << "Deleted a Command." << endl;
	
	delete myInputString;
	delete myEffect;

	myInputString = nullptr;
	myEffect = nullptr;
};

// Save the given string, usually an error message, as the command's "effect".
void Command::saveEffect(string* effectString)
{
	myEffect = effectString; // Should this be generated here instead of being passed as a parameter?
};

// Assignment operator overload
void Command::operator=(Command& Command)
{
	cout << "\nCommand assignment operator called." << endl;
	myInputString = Command.myInputString;
	myEffect = Command.myEffect;
}

// Stream insertion operator overload.
ostream& operator<<(ostream& os, const Command& command) {
	os << "\nCommand stream insertion operator called" << endl;

	os << "Input string: " << *(command.myInputString) << endl;
	if (command.myEffect != nullptr)
		os << "Effect string: " << *(command.myEffect) << endl;;
	
	return os;
}



// COMMAND PROCESSOR
CommandProcessor::CommandProcessor()
{
	//commands = {}; // Init the empty command vector.
}

// Read the current contents of the console, and create a command from the resulting string.
void CommandProcessor::readCommand()
{
	cout << "\nPlease type in the next command, then press Enter: ";
	
	string inputString;
	getline(cin, inputString);

	saveCommand(inputString);
};

// Create a command from the given input string, and add it to the list of commands.
void CommandProcessor::saveCommand(string inputString)
{
	Command* newCommand = new Command(inputString);
	commands.push(newCommand);
};

// 
Command* CommandProcessor::getCommand()
{
	readCommand();
	return commands.top();
};

//bool validate();