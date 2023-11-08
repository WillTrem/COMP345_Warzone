#include "GameEngine.h"

// Default constuctor for GameEngine
GameEngine::GameEngine()
{
    GameState startState = START;
    currentState = &startState;
    stateTransitions = nullptr;

    deck = new Deck();
    players = new std::vector<Player*>;

    commandProcessor = new CommandProcessor(); // The command processor to create depends on a command line parameter. How to handle this here?
}

/**
 * Normal constructor
 */
GameEngine::GameEngine(GameState *currentState, std::map<GameState, std::list<Command>> *stateTransitions, bool fromFile, string fileName) : currentState(currentState),
                                                                                                                                             stateTransitions(stateTransitions)
{
    deck = new Deck();
    players = new std::vector<Player*>;

    if (fromFile)
    {
        FileCommandProcessorAdapter *adapter = new FileCommandProcessorAdapter(fileName);
        commandProcessor = adapter;
    }
    else
        commandProcessor = new CommandProcessor();
}

/**
 * Copy constructor
 */
GameEngine::GameEngine(const GameEngine &gameEngine) : currentState(gameEngine.currentState),
                                                       stateTransitions(gameEngine.stateTransitions),
                                                       deck(gameEngine.deck)
{
    players = {}; // Need to copy these also.

    // How to handle the source's command processor being from a file?
    FileCommandProcessorAdapter *temp = dynamic_cast<FileCommandProcessorAdapter *>(gameEngine.commandProcessor);
    if (temp == nullptr)
        commandProcessor = new CommandProcessor(*(gameEngine.commandProcessor));
    else
    {
        FileCommandProcessorAdapter *adapter = new FileCommandProcessorAdapter(*temp);
        commandProcessor = adapter;
    }
}

// Destructor
GameEngine::~GameEngine()
{
    delete commandProcessor;
    commandProcessor = nullptr;
    
    delete currentState;
    currentState = nullptr;

    delete gameMap;
    gameMap = nullptr;

    delete players;
    players = nullptr;

    delete deck;
    deck = nullptr;
}

void GameEngine::mainGameLoop()
{
    reinforcementPhase();
    issueOrdersPhase();
    executeOrdersPhase();
}

void GameEngine::reinforcementPhase()
{
    for (auto player : *players)
    {
        // Check which continents player occupies
        vector<Continent> continentsOccupied;
        for (auto continent : gameMap->continents)
        {
            // assume its occupied and go through the list
            bool occupied = true;
            for (auto territory : continent->continentTerritories)
            {
                if (territory->occupierName.compare(player->getPlayerName()) != 0)
                {
                    occupied = false;
                    break;
                }
            }

            if (occupied)
            {
                continentsOccupied.push_back(*continent);
            }
        }

        // Give player continent bonus(es)
        int continentBonus = 0;
        for (auto continent : continentsOccupied)
        {
            continentBonus += continent.controlBonus;
        }

        // Allocate units to player
        int units = player->getOwnedTerritories().size() / 3 + continentBonus;
        if (units >= 3)
        {
            player->setReinforcementPool(units);
        }
        else
        {
            player->setReinforcementPool(3);
        }
    }
}

void GameEngine::issueOrdersPhase()
{
}

void GameEngine::executeOrdersPhase()
{
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
    for (auto &cmd : (*stateTransitions)[*currentState])
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
void GameEngine::executeCommand(Command *command)
{
    bool cmdSucessful = false;

    // We assume that the input command has already been validated.

    // These actions should probably be stored inside of the commands themselves, but I'm not sure how to approach it. Assign them in the command's validate function?
    //
    // Switch cases are not useable with strings :/
    if (command->cmdName == "loadmap")
    {
        gameMap = new Map();
        gameMap->loadMap(command->parameter); // Assuming the map's filename is stored in the command's parameter field..

        cout << "Successfully loaded map " << gameMap->mapName << ".\n\n" << endl;

        currentState = command->nextState;
        cmdSucessful = true;
    }
    if (command->cmdName == "validatemap")
    {
        gameMap->validate();

        cout << "\nSuccessfully validated map " << gameMap->mapName << ".\n\n" << endl;

        currentState = command->nextState;
        cmdSucessful = true;
    }
    if (command->cmdName == "addplayer")
    {
        if (players->size() < 6)
        {
            Player* newPlayer = new Player(command->parameter); // Assuming the player's name is stored in the command's parameter field.
            players->push_back(newPlayer);

            cout << "New player " << newPlayer->getPlayerName() << " has beed added to the game.\n" << endl;

            currentState = command->nextState;
            cmdSucessful = true;
        }
        else
            cout << "The game is full; additional players may not be added.\n" << endl;
    }
    if (command->cmdName == "gamestart" && players->size() > 1)
    {
        cout << "Preparing to begin the game...\n\n" << endl;
        
        // Fairly distribute all the territories to the players.
        // What to do if they cannot be evenly divided?
        int numPlayers = players->size();
        int numTerritories = gameMap->mapTerritories.size();

        for (int i = 0; i < numTerritories; i++)
        {
            int playerIndex = i % numPlayers;

            // Assign the territory at gameMap->mapTerritories[i] to the player at players[playerIndex].
            players->at(playerIndex)->addOwnedTerritory(gameMap->mapTerritories.at(i));
            gameMap->mapTerritories.at(i)->occupierName = players->at(playerIndex)->getPlayerName();

            cout << "Assigned territory " << gameMap->mapTerritories.at(i)->territoryName << " to player " << players->at(playerIndex)->getPlayerName() << ".\n" << endl;
        }

        // Determine randomly the order of play of the players in the game.
        std::random_device randomizer;
        std::mt19937 twister(randomizer());
        std::shuffle(players->begin(), players->end(), twister); // Shuffle the players vector so they won't necessarily go in their input order.

        // Doing both steps C and D in the same loop for efficiency's sake.
        for (int i = 0; i < numPlayers; i++)
        {
            // Give 50 initial army units to the players, which are placed in their respective reinforcement pool.
            players->at(i)->setReinforcementPool(players->at(i)->getReinforcmentPool() + 50);
            cout << "\nAwarded 50 reinforcement units to player " << players->at(i)->getPlayerName() << ".\n" << endl;

            // Let each player draw 2 initial cards from the deck using the deck's draw() method.
            Hand * currentHand = players->at(i)->getHand();
            deck->draw(currentHand);
            deck->draw(currentHand);
        }

        // switch the game to the play phase
        cout << "StartUp phase completed. The game will now begin.\n" << endl;

        currentState = command->nextState;
        cmdSucessful = true;
    }

    if (!cmdSucessful)
    {
        if (players->size() == 1)
        {
            std::cout << "Please add at least one more player before starting the game.\n" << std::endl;
        }
        
        std::cout << "Something went wrong executing the command.\n" << std::endl;
    }
}

void GameEngine::startupPhase()
{
    Command *currentCommand = nullptr;

    while (*currentState != ASSIGN_REINFORCEMENTS) // Remain in the startup phase until we switch to the gamestart/play phase.
    {
        currentCommand = commandProcessor->getCommand();
        //cout << "Current command: " << currentCommand->cmdName << endl;

        if (commandProcessor->validate(currentCommand, *currentState))
        {
            executeCommand(currentCommand); // Execute the command; change the game engine's state.

            //cout << "Current state: " << *currentState << endl << endl;
        }
        else
            cout << "Invalid command. Please re-enter.\n"
                 << endl;
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
