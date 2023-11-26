#include "GameEngine.h"

// Default constructor for GameEngine
GameEngine::GameEngine()
{
    currentState = new GameState(START); // Allocate a new GameState on the heap
    stateTransitions = nullptr;

    deck = new Deck();

    Player *p1 = new Player("player1");
    Player *p2 = new Player("player2");
    Player *p3 = new Player("player3");
    Player *p4 = new Player("player4");

    players = new std::vector<Player *>();

    players->push_back(p1);
    players->push_back(p2);
    players->push_back(p3);
    players->push_back(p4);

    commandProcessor = new CommandProcessor();
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

string GameEngine::gameStateToString(GameState state) const
{
    switch (state)
    {
    case START:
        return "START";
    case MAP_LOADED:
        return "MAP_LOADED";
    case MAP_VALIDATED:
        return "MAP_VALIDATED";
    case PLAYERS_ADDED:
        return "PLAYERS_ADDED";
    case ASSIGN_REINFORCEMENTS:
        return "ASSIGN_REINFORCEMENTS";
    case ISSUE_ORDERS:
        return "ISSUE_ORDERS";
    case EXECUTE_ORDERS:
        return "EXECUTE_ORDERS";
    case WIN:
        return "WIN";
    case END:
        return "END";
    default:
        return "UNKNOWN";
    }
}

// Function called during state transitions; here for ease of notification.
void GameEngine::transition(GameState *newState)
{
    if (currentState != nullptr)
    {
        *currentState = *newState;
        Notify(*this);
    }
}

string GameEngine::stringToLog() const
{
    if (currentState != nullptr)
    {
        return "Game Engine Log: Game Engine transitioned to state - " + gameStateToString(*currentState);
    }
    else
    {
        return "";
    }
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
            transition(cmd.nextState);
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

// Main start up phase method.
// Executes the inputed commands as they are received or read.
// Asks for the command to be re-entered if it is not valid.
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

// General method for the main game loop, assembling its sub-elements.
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
        //vector<Territory *> territoriesToAttack = player->toAttack();
        //vector<Territory *> territoriesToDefend = player->toDefend();
        player->toAttack();
        player->toDefend();

        /*
            Deploy units from reinforcement pool
        */
        string territoryList = "";
        for (int i = 0; i < player->territoriesToDefend.size(); i++)
        {
            territoryList += player->territoriesToDefend[i]->territoryName + "( " + std::to_string(i) + " ), ";
        }

        int numUnits = player->getReinforcmentPool();
        int unitsDeployed = 0;
        while (unitsDeployed < numUnits)
        {
            std::cout << "Deploy units to which territory? " << territoryList << std::endl;
            string territory;
            std::cin >> territory;
            int tIndex = std::stoi(territory);

            if (!(tIndex >= 0 && tIndex < player->territoriesToDefend.size()))
            {
                std::cout << "Invalid territory number/index" << std::endl;
            }

            std::cout << "How many units? " << std::endl;
            string units;
            std::cin >> units;
            int unitsI = std::stoi(units);

            if (unitsI > 0 && unitsI + unitsDeployed <= numUnits)
            {
                // TODO: implement Deploy constructor and issueOrder method in Player.cpp
                // Deploy order(territories[tIndex], unitsI);
                // player->issueOrder(order);
                unitsDeployed += unitsI;
            }
            else
            {
                std::cout << "Invalid number of units (1 - units left in pool) " << std::endl;
            }
        }

        /*
            Advance orders
        */

        // Advance to defend
        for (auto territory1 : player->territoriesToDefend)
        {
            for (auto territory2 : player->territoriesToDefend)
            {
                if (territory1->territoryName.compare(territory2->territoryName) != 0)
                {
                    std::cout << "Advance units from " << territory1->territoryName << " to " << territory2->territoryName << "? (y/n)" << std::endl;
                    string answer;
                    std::cin >> answer;
                    if (answer.compare("y") == 0)
                    {
                        std::cout << "How many units? " << std::endl;
                        string units;
                        std::cin >> units;

                        Advance *advance = new Advance(player, std::stoi(units), territory1, territory2);
                        player->issueOrder(advance);
                        break;
                    }
                }
            }
        }

        // Advance to attack
        for (auto territory1 : player->territoriesToDefend)
        {
            for (auto territory2 : player->territoriesToAttack)
            {
                if (territory1->territoryName.compare(territory2->territoryName) != 0)
                {
                    std::cout << "Advance units from " << territory1->territoryName << " to " << territory2->territoryName << "? (y/n)" << std::endl;
                    string answer;
                    std::cin >> answer;
                    if (answer.compare("y") == 0)
                    {
                        std::cout << "How many units? " << std::endl;
                        string units;
                        std::cin >> units;

                        Advance *advance = new Advance(player, std::stoi(units), territory1, territory2);
                        player->issueOrder(advance);
                        break;
                    }
                }
            }
        }

        /*
            Issue order from one card in hand
        */
        for (auto card : player->getHand()->returnMyCards())
        {
            string cardType = "";

            if (dynamic_cast<Card_Airlift *>(card) != nullptr)
            {
                cardType = "an Airlift";
            }
            else if (dynamic_cast<Card_Blockade *>(card) != nullptr)
            {
                cardType = "a Blockade";
            }
            else if (dynamic_cast<Card_Bomb *>(card) != nullptr)
            {
                cardType = "a Bomb";
            }
            else if (dynamic_cast<Card_Diplomacy *>(card) != nullptr)
            {
                cardType = "a Diplomacy";
            }
            else
            {
                cardType = "a Reinforcement";
            }

            std::cout << "Play " << cardType << "card? (y/n)" << std::endl;
            string answer;
            std::cin >> answer;
            if (answer.compare("y") == 0)
            {
                card->play();
                break;
            }
        }
    }
}

void GameEngine::executeOrdersPhase()
{
    for (auto player : *players)
    {

        OrdersList *orderList = player->getOrdersList();
        Order *nextOrder = orderList->getNextOrder();
        while (nextOrder != nullptr)
        {
            nextOrder->execute();
        }
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
