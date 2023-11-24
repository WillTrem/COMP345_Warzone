#include "PlayerStrategyDriver.h"

void testPlayerStrategies()
{

    // Player Creation
    Player HumanPlayer("Timmy");
    Player AngryBot("");
    Player NiceBot("");
    Player NeutralBot("");
    Player CheatBot("");

    // Order Creation

    // Setting the strategy for each player
    AngryBot.setStrategy(new AggressivePlayerStrategy());
    NiceBot.setStrategy(new BenevolentPlayerStrategy());
    NeutralBot.setStrategy(new NeutralPlayerStrategy());
    CheatBot.setStrategy(new CheaterPlayerStrategy());

    std::cout << "reached toAttack()" << endl;
    // Testing toAttack() method with all computer players
    AngryBot.toAttack();
    NiceBot.toAttack();
    NeutralBot.toAttack();
    CheatBot.toAttack();

    // std::cout << "reached toDefend()" << endl;
    // // Testing toDefend() method will all computer players
    // AngryBot.toDefend();
    // NiceBot.toDefend();
    // NeutralBot.toDefend();
    // CheatBot.toDefend();

    // std::cout << "reached issueOrder(order)" << endl;
    // // Testing toDefend() method will all computer players
    // AngryBot.issueOrder();
    // NiceBot.issueOrder();
    // NeutralBot.issueOrder();
    // CheatBot.issueOrder();
}