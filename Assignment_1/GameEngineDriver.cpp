#include "GameEngine.h"
#include <string>

void testGameEngine()
{
    GameEngine gameEngine;

    while (gameEngine.currentState != GameState::END)
    {
        std::cout << "> ";
        std::string command;
        std::cin >> command;
        gameEngine.executeCommand(command);
    }
}