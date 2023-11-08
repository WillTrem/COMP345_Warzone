#include "GameEngine.h"
#include "CommandProcessing.h"
#include "CommandProcessingDriver.h"

void testCommandProcessor(){

	cout << "\nTesting the command processors.\n" << endl;

	CommandProcessor* consoleCP = new CommandProcessor();
	CommandProcessor* fileCP = new FileCommandProcessorAdapter("test.txt");
	
	cout << "Base command processor:\n" << endl;
	Command* consoleCommand = consoleCP->getCommand();
	bool isCommandValid = consoleCP->validate(consoleCommand, START);
	cout<<isCommandValid<<endl;
	
	cout << "\nFile command processor:\n" << endl;
	Command* fileCommand = fileCP->getCommand();
	cout << "\nGot command.\n" << endl;

	isCommandValid = fileCP->validate(fileCommand, START);
	cout<<isCommandValid<<endl;
	cout << "\nCommand validated.\n" << endl;

	cout << "\Done testing command processing." << endl;

}