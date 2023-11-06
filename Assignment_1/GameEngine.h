#pragma once

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <functional>

// #include "Orders.h"
#include "Cards.h"
#include "Player.h"
#include "CommandProcessing.h"


// Moved GameStates and Command to the CommandProcessing file.


class GameEngine
{
private:
    std::map<GameState, std::list<Command>> *stateTransitions;

public:
    GameState *currentState;
    CommandProcessor* commandProcessor;


    // Constructors
    GameEngine();
    GameEngine(GameState *currentState, std::map<GameState, std::list<Command>> *stateTransitions);
    GameEngine(const GameEngine &gameEngine);

    void executeCommand(std::string command);

    void startupPhase();

    // Operator overloads
    void operator=(GameState &newState);
	friend std::ostream& operator<<(std::ostream &os, const GameEngine& gameEngine);

};