#include "GameEngine.h"

// Default constuctor for GameEngine
GameEngine::GameEngine()
{
    GameState startState = START;
    currentState = &startState;
    stateTransitions = nullptr;

    deck = new Deck();
    players = new std::vector<Player *>;

    commandProcessor = new CommandProcessor(); // The command processor to create depends on a command line parameter. How to handle this here?
}

/**
 * Normal constructor
 */
GameEngine::GameEngine(GameState *currentState, std::map<GameState, std::list<Command>> *stateTransitions, bool fromFile, string fileName) : currentState(currentState),
                                                                                                                                             stateTransitions(stateTransitions)
{
    deck = new Deck();
    players = new std::vector<Player *>;

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
            std::cout << "+" << units << " units in " << player->getPlayerName() << "'s reinforcement pool" << std::endl;
            player->setReinforcementPool(units);
        }
        else
        {
            std::cout << "+3 units in " << player->getPlayerName() << "'s reinforcement pool" << std::endl;

            player->setReinforcementPool(3);
        }
    }
}

void GameEngine::issueOrdersPhase()
{
    for (auto player : *players)
    {
        vector<Territory *> territories = player->getOwnedTerritories();
        /*
            Deploy units from reinforcement pool
        */
        string territoryList = "";
        for (int i = 0; i < territories.size(); i++)
        {
            territoryList += territories[i]->territoryName + "( " + std::to_string(i) + " ), ";
        }

        int numUnits = player->getReinforcmentPool();
        int unitsDeployed = 0;
        while (unitsDeployed < numUnits)
        {
            std::cout << "Deploy units to which territory? " << territoryList << std::endl;
            string territory;
            std::cin >> territory;
            int tIndex = std::stoi(territory);

            if (!(tIndex >= 0 && tIndex < territories.size()))
            {
                std::cout << "Invalid territory number/index" std::endl;
            }

            std::cout << "How many units? " << std::endl;
            string units;
            std::cin >> units;
            int unitsI = std::stoi(units);

            if (unitsI > 0 && unitsI + unitsDeployed <= numUnits)
            {
                // Deploy order(territories[tIndex], unitsI);
                // player->issueOrder(order);
                unitsDeployed += unitsI;
            }
            else
            {
                std::cout << "Invalid number of units (1 to units left in pool) " std::endl;
            }
        }

        /*
            Attack and defend
        */
        player->toAttack();
        player->toDefend();
    }
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
    // We assume that the input command has already been validated.

    bool cmdSucessful = (command->*command->execution)(currentState, gameMap, players, deck);
    // cout << "Current state: " << *currentState << endl;

    if (!cmdSucessful)
    {
        std::cout << "Something went wrong executing the command.\n"
                  << std::endl;
    }
}

void GameEngine::startupPhase()
{
    Command *currentCommand = nullptr;

    while (*currentState != ASSIGN_REINFORCEMENTS) // Remain in the startup phase until we switch to the gamestart/play phase.
    {
        currentCommand = commandProcessor->getCommand();
        // cout << "Current command: " << currentCommand->cmdName << endl;

        if (commandProcessor->validate(currentCommand, *currentState))
        {
            executeCommand(currentCommand); // Execute the command; change the game engine's state.

            // cout << "Current state: " << *currentState << endl << endl;
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
