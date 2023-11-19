#include "PlayerStrategyDriver.h"

void testPlayerStrategies()
{
    // Player Creation
    Player HumanPlayer("Timmy");
    Player AngryBot("");
    Player NiceBot("");
    Player NeutralBot("");
    Player CheatBot("");

    // Setting the strategy for each player
    AngryBot.setStrategy(new AggressivePlayerStrategy());
    NiceBot.setStrategy(new BenevolentPlayerStrategy());
    NeutralBot.setStrategy(new NeutralPlayerStrategy());
    CheatBot.setStrategy(new CheaterPlayerStrategy());
}