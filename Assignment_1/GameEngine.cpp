#include "GameEngine.h"


// Default constuctor for GameEngine
GameEngine::GameEngine(){
    GameState startState = START;
    currentState = &startState;
    stateTransitions = nullptr;

    players = {};

    commandProcessor = new CommandProcessor(); // The command processor to create depends on a command line parameter. How to handle this here?
}

/**
 * Normal constructor
*/
GameEngine::GameEngine(GameState* currentState, std::map<GameState, std::list<Command>>* stateTransitions, bool fromFile, string fileName) :
    currentState(currentState), 
    stateTransitions(stateTransitions) 
{
    players = {};
    
    if (fromFile)
    {
        FileCommandProcessorAdapter* adapter = new FileCommandProcessorAdapter(fileName);
        commandProcessor = adapter;
    }
    else 
        commandProcessor = new CommandProcessor();
}

/**
 * Copy constructor
*/
GameEngine::GameEngine(const GameEngine &gameEngine): 
    currentState(gameEngine.currentState), 
    stateTransitions(gameEngine.stateTransitions) 
{
    players = {}; // Need to copy these also.
    
    // How to handle the source's command processor being from a file?
    FileCommandProcessorAdapter* temp = dynamic_cast<FileCommandProcessorAdapter*>(gameEngine.commandProcessor);
    if (temp == nullptr)
        commandProcessor = new CommandProcessor(*(gameEngine.commandProcessor));
    else
    {
        FileCommandProcessorAdapter* adapter = new FileCommandProcessorAdapter(*temp);
        commandProcessor = adapter;
    }
    
}

// Destructor
GameEngine::~GameEngine()
{
    delete currentState;
    currentState = nullptr;

    delete gameMap;
    gameMap = nullptr;

    delete commandProcessor;
    commandProcessor = nullptr;

}


/**
 * 1. Checks to see if the commmand is a valid command at the current state
 * 2. executes the transistion function (action)
 * 3. Make currentState point to the new state
*/
void GameEngine::executeCommand(std::string commandArg)
{
    bool cmdSucessful = false;

    // passed by reference instead of value so no new variables are created
    for (auto& cmd : (*stateTransitions)[*currentState])
    {
        if ((cmd.cmdName) == commandArg)
        {
            cmd.action();
            currentState = cmd.nextState;
            cmdSucessful = true;
        }
    }

    if (!cmdSucessful)
    {
        std::cout << "Invalid command. See above for valid commands" << std::endl;
    }
}

// Overload of executeCommand which takes in an actual command object.
void GameEngine::executeCommand(Command* command)
{
    bool cmdSucessful = false;

    // We assume that the input command has already been validated.

    // These actions should probably be stored inside of the commands themselves, but I'm not sure how to approach it.
    // 
    // Switch cases are not useable with strings :/
    if (command->cmdName == "loadmap")
    {
        gameMap = new Map();
        gameMap->loadMap(command->parameter); // Assuming the map's filename is stored in the command's parameter field.

        currentState = command->nextState;
        cmdSucessful = true;
    }
    if (command->cmdName == "validatemap")
    {
        gameMap->validate();

        currentState = command->nextState;
        cmdSucessful = true;
    }
    if (command->cmdName == "addplayer")
    {
        if (players->size() < 6)
        {
            cout << "Creating a new player, " << command->parameter << "." << endl;
            Player* newPlayer = new Player(command->parameter); // Assuming the player's name is stored in the command's parameter field.
            players->push_back(*newPlayer);

            currentState = command->nextState;
            cmdSucessful = true;
        }
        else
            cout << "The game is full; additional players may not be added." << endl;
    }
    if (command->cmdName == "gamestart")
    {
        // Fairly distribute all the territories to the players
        // What to do if they cannot be evenly divided?
        int numPlayers = players->size();
        int numTerritories = gameMap->mapTerritories.size();
        
        for (int i = 0; i < numTerritories; i++)
        {
            int playerIndex = i % numPlayers; 
            // Assign the territory at gameMap->mapTerritories[i] to the player at players[playerIndex].
        }


        // Determine randomly the order of play of the players in the game
        std::random_device randomizer;
        std::mt19937 twister(randomizer());
        std::shuffle(players->begin(), players->end(), twister); // Shuffle the players vector so they won't necessarily go in their input order.

        // give 50 initial army units to the players, which are placed in their respective reinforcement pool
        // let each player draw 2 initial cards from the deck using the deck’s draw() method
        // switch the game to the play phase
    }


    if (!cmdSucessful)
    {
        std::cout << "Something went wrong executing the command." << std::endl;
    }
}



void GameEngine::startupPhase()
{
    Command* currentCommand = nullptr;

    while (*currentState != ASSIGN_REINFORCEMENTS) // Remain in the startup phase until we switch to the gamestart/play phase.
    {
        currentCommand = commandProcessor->getCommand();
        if (commandProcessor->validate(currentCommand, *currentState))
        {
            executeCommand(currentCommand); // Execute the command; change the game engine's state.
        }
        else
            cout << "Invalid command. Please re-enter.\n" << endl;
    }
}


void GameEngine::operator=(GameState &newState)
{
    currentState = &newState;
}

std::ostream &operator<<(std::ostream &os, const GameEngine &gameEngine)
{
    os << "Current state = state " << gameEngine.currentState << std::endl;
    return os;
}
