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

class GameEngine : public Subject, public ILoggable
{
private:
    std::map<GameState, std::list<Command>> *stateTransitions;

    // Executive functions used by commands.
    bool loadMap();
    bool validateMap();
    bool addPlayer();
    bool gameStart();

public:
    GameState *currentState;

    Deck *deck;
    Map *gameMap;
    std::vector<Player *> *players;

    CommandProcessor *commandProcessor;

    // Constructors
    GameEngine();
    GameEngine(GameState *currentState, std::map<GameState, std::list<Command>> *stateTransitions, bool fromFile = false, string fileName = "test");
    GameEngine(const GameEngine &gameEngine);

    ~GameEngine();

    void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();

    void executeCommand(std::string command);
    void executeCommand(Command *command);

    void startupPhase();

    // Operator overloads
    void operator=(GameState &newState);
    friend std::ostream &operator<<(std::ostream &os, const GameEngine &gameEngine);
};