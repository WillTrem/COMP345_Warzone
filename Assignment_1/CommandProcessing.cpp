#pragma once

#include "CommandProcessing.h"

using namespace std;

// COMMAND
Command::Command(string* inputString)
{
	myInputString = inputString;
	myEffect = nullptr; // Initially, we have no effect string.
};
Command::Command()
{
	myInputString = new string; // Create an empty dummy string.
	myEffect = nullptr; // Initially, we have no effect string.
};

// Save the given string, usually an error message, as the command's "effect".
void Command::saveEffect(string* effectString)
{
	myEffect = effectString; // Should this be generated here instead of being passed as a parameter?
};


// COMMAND PROCESSOR
CommandProcessor::CommandProcessor()
{
	commands = {}; // Init the empty command vector.
}

// Read the current contents of the console, and create a command from the resulting string.
string CommandProcessor::readCommand()
{
	string inputString;
	getline(cin, inputString);

	saveCommand(&inputString);
};

// Create a command from the given input string, and add it to the list of commands.
void CommandProcessor::saveCommand(string* inputString)
{
	Command newCommand = Command(inputString);
	commands.append(newCommand);
};