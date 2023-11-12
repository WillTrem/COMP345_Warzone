
#include "CommandProcessingDriver.h"

void testCommandProcessor()
{

	cout << "\nTesting the command processors.\n"
		 << endl;

	CommandProcessor *consoleCP = new CommandProcessor();
	CommandProcessor *fileCP = new FileCommandProcessorAdapter("test.txt");

	cout << "\nBase command processor:\n"
		 << endl;
	Command *consoleCommand = consoleCP->getCommand();
	bool isCommandValid = consoleCP->validate(consoleCommand, START);
	cout << "Is this command valid? " << isCommandValid << endl;

	cout << "\n\nFile command processor:\n"
		 << endl;
	Command *fileCommand = fileCP->getCommand();
	isCommandValid = fileCP->validate(fileCommand, START);
	cout << "Is this command valid? " << isCommandValid << endl;

	cout << "\n\nDone testing command processing.\n\n"
		 << endl;
}