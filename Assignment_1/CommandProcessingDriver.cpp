#include "GameEngine.h"
#include "CommandProcessing.h"
#include "CommandProcessingDriver.h"

void testCommandProcessor(){
	CommandProcessor* consoleCP = new CommandProcessor();
	CommandProcessor* fileCP = new FileCommandProcessorAdapter("test.txt");
	
	Command* consoleCommand = consoleCP->getCommand();
	bool isCommandValid = consoleCP->validate(consoleCommand, START);
	cout<<isCommandValid<<endl;
	
	Command* fileCommand = fileCP->getCommand();

	isCommandValid = fileCP->validate(fileCommand, WIN);
	cout<<isCommandValid<<endl;

}