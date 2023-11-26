#pragma once

#include "PlayerStrategyDriver.h"

void testPlayerStrategies()
{
    // Prepare the game engine; most of this code reused from Assignment 2.

    GameState START = GameState::START;
    GameState MAP_LOADED = GameState::MAP_LOADED;
    GameState MAP_VALIDATED = GameState::MAP_VALIDATED;
    GameState PLAYERS_ADDED = GameState::PLAYERS_ADDED;
    GameState ASSIGN_REINFORCEMENTS = GameState::ASSIGN_REINFORCEMENTS;
    GameState ISSUE_ORDERS = GameState::ISSUE_ORDERS;
    GameState EXECUTE_ORDERS = GameState::EXECUTE_ORDERS;
    GameState WIN = GameState::WIN;
    GameState END = GameState::END;

    std::string loadMapCmd = "loadMap";
    std::string validateMapCmd = "validateMap";
    std::string addPlayerCmd = "addPlayer";
    std::string assignCountriesCmd = "assignCountries";
    std::string issueOrderCmd = "issueOrder";
    std::string endIssueOrdersCmd = "endIssueOrders";
    std::string executeOrderCmd = "executeOrder";
    std::string endExecuteOrdersCmd = "endExecuteOrders";
    std::string winCmd = "win";
    std::string playCmd = "play";
    std::string endCmd = "end";

    // Game Engine FSM
    std::map<GameState, std::list<Command>> stateTransitions = {
        // Start states
        {GameState::START, {Command(&loadMapCmd, loadMap, &MAP_LOADED)}},
        {GameState::MAP_LOADED, {Command(&loadMapCmd, loadMap, &MAP_LOADED), Command(&validateMapCmd, validateMap, &MAP_VALIDATED)}},
        {GameState::MAP_VALIDATED, {Command(&addPlayerCmd, addPlayer, &PLAYERS_ADDED)}},
        {GameState::PLAYERS_ADDED, {Command(&addPlayerCmd, addPlayer, &PLAYERS_ADDED), Command(&assignCountriesCmd, assignCountries, &ASSIGN_REINFORCEMENTS)}},
        // Play states
        {GameState::ASSIGN_REINFORCEMENTS, {Command(&issueOrderCmd, issueOrder, &ISSUE_ORDERS)}},
        {GameState::ISSUE_ORDERS, {Command(&issueOrderCmd, issueOrder, &ISSUE_ORDERS), Command(&endIssueOrdersCmd, endIssueOrders, &EXECUTE_ORDERS)}},
        {GameState::EXECUTE_ORDERS, {Command(&executeOrderCmd, executeOrder, &EXECUTE_ORDERS), Command(&endExecuteOrdersCmd, endExecuteOrders, &ASSIGN_REINFORCEMENTS), Command(&winCmd, win, &WIN)}},
        {GameState::WIN, {Command(&playCmd, start, &START), Command(&endCmd, end, &END)}},
    };

    GameState currentState = GameState::START;

    GameEngine* gameEngine = new GameEngine(&currentState, &stateTransitions, true, "test.txt");

    // Create cards to be drawn from.
    cout << "\nGenerating some cards for testing...\n"
        << endl;
    Card_Bomb cardBombTest = Card_Bomb(gameEngine->deck);
    Card_Bomb cardBombTest2 = Card_Bomb(gameEngine->deck);
    Card_Reinforcement cardReinforcementTest = Card_Reinforcement(gameEngine->deck);
    Card_Reinforcement cardReinforcementTest2 = Card_Reinforcement(gameEngine->deck);
    Card_Blockade cardBlockadeTest = Card_Blockade(gameEngine->deck);
    Card_Blockade cardBlockadeTest2 = Card_Blockade(gameEngine->deck);
    Card_Airlift carAirliftTest = Card_Airlift(gameEngine->deck);
    Card_Airlift carAirliftTest2 = Card_Airlift(gameEngine->deck);
    Card_Diplomacy carDiplomacyTest = Card_Diplomacy(gameEngine->deck);
    Card_Diplomacy carDiplomacyTest2 = Card_Diplomacy(gameEngine->deck);

    cout << "\nGame start up phase.\n" << endl;
    gameEngine->startupPhase();
    

    // Tag the players generated from the text file.
    Player* humanPlayer = gameEngine->players->at(0);
    Player* angryBot = gameEngine->players->at(1);
    Player* niceBot = gameEngine->players->at(2);
    Player* neutralBot = gameEngine->players->at(3);
    Player* cheaterBot = gameEngine->players->at(4);

    // Assign each player their strategy.
    humanPlayer->setStrategy(new HumanPlayerStrategy());
    angryBot->setStrategy(new AggressivePlayerStrategy());
    niceBot->setStrategy(new BenevolentPlayerStrategy());
    neutralBot->setStrategy(new NeutralPlayerStrategy());
    cheaterBot->setStrategy(new CheaterPlayerStrategy());

    cout << "\n\nAll players have been assigned their respective strategies.\n" << endl;


    //std::cout << "reached toAttack()" << endl;
    //// Testing toAttack() method with all computer players
    //AngryBot.toAttack();
    //NiceBot.toAttack();
    //NeutralBot.toAttack();
    //CheatBot.toAttack();

    //// Print the contents of AngryBot's territoriesToAttack vector.
    //for (auto territory : AngryBot.territoriesToAttack)
    //{
    //    cout << "AngryBot wants to attack " << territory->territoryName << endl;
    //}

    //std::cout << "reached toDefend()" << endl;
    //// // Testing toDefend() method will all computer players
    //// AngryBot.toDefend();
    //// NiceBot.toDefend();
    //// NeutralBot.toDefend();
    //// CheatBot.toDefend();

    //std::cout << "reached issueOrder(order)" << endl;
    //// // Testing toDefend() method will all computer players
    //// AngryBot.issueOrder();
    //// NiceBot.issueOrder();
    //// NeutralBot.issueOrder();
    //// CheatBot.issueOrder();
}