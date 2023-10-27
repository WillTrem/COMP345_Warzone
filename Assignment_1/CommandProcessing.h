#pragma onces

#include <iostream>
#include <string>
#include <vector>

// PART 1.
// 
// Implement a CommandProcessor class, a FileCommandProcessorAdapter class.
// All the classes / functions that you implement for this component must all reside in a single.cpp / .h file duo named CommandProcessing.cpp / CommandProcessing.h.

// Written by Roxane Morin, 40191881.

using namespace std;

class Command
{
	private:
	// Variables
	string* myInputString;
	string* myEffect;

	public:
	// Constructors
	Command(string* inputString);
	Command(); // Parameter-free constructor just in case.

	// Methods
	void saveEffect(string* effectString);
};

class CommandProcessor
{
	private:
	// Variables
	vector <Command*­> commands;

	// Methods
	string readCommand();
	void saveCommand(string* inputString);


	public:
	// Constructor
	CommandProcessor();

	// Methods
	Command getCommand();
	bool validate();

};

