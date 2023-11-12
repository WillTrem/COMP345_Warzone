#pragma once

#include <map>
#include <list>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <random>

// #include "Orders.h"
#include "Cards.h"
#include "Player.h"
#include "CommandProcessing.h"
#include "LogObserver.h"

// Moved GameStates and Command to the CommandProcessing file.
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
class GameEngine : public Subject, public ILoggable
{
private:
    std::map<GameState, std::list<Command> > *stateTransitions;

public:
    GameState *currentState;

    Deck *deck;
    Map *gameMap;
    std::vector<Player *> *players;

    CommandProcessor *commandProcessor;

    // Constructors
    GameEngine();
    GameEngine(GameState *currentState, std::map<GameState, std::list<Command> > *stateTransitions, bool fromFile = false, string fileName = "test");
    GameEngine(const GameEngine &gameEngine);

    ~GameEngine();

    void transition(GameState *newState);

    void executeCommand(std::string command);
    void executeCommand(Command *command);

    void startupPhase();

    // Function to log to GameLog.txt
    string stringToLog() const override;

    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

    // Operator overloads
    void operator=(GameState &newState);
    friend std::ostream &operator<<(std::ostream &os, const GameEngine &gameEngine);
};
#endif // GAMEENGINE_H
