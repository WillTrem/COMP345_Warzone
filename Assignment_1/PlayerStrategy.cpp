#include "PlayerStrategy.h"

// Constants.
const int NUM_TO_ATTACK_DEFENSIVE = 0;
const int NUM_TO_DEFEND_DEFENSIVE = 4;

const int NUM_TO_ATTACK_AGGRESSIVE = 2;
const int NUM_TO_DEFEND_AGGRESIVE = 2;

// Constructors.
PlayerStrategy::PlayerStrategy(Player *player)
{
    p = player;
    cout << "\nAssigned a player strategy to " << p->getPlayerName() << endl;
}

HumanPlayerStrategy::HumanPlayerStrategy(Player *player) : PlayerStrategy(player)
{
    // Implementation if needed
    cout << "It is the Human player strategy." << endl;
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) : PlayerStrategy(player)
{
    // Implementation if needed
    cout << "It is the Aggressive player strategy." << endl;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player) : PlayerStrategy(player)
{
    // Implementation if needed
    cout << "It is the Benevolent player strategy." << endl;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) : PlayerStrategy(player)
{
    // Implementation if needed
    cout << "It is the Neutral player strategy." << endl;
}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player) : PlayerStrategy(player)
{
    // Implementation if needed
    cout << "It is the Cheater player strategy." << endl;
}

// Abstract strategy class

// Returns a vector of all enemy territories adjacent to the player's. For use by AI players.
vector<Territory *> PlayerStrategy::getAdjacentTerritories()
{
    // Using a set in order to avoid duplicates.
    set<Territory *> temp;

    for (Territory *myTerritory : p->getOwnedTerritories()) // For each of the player's owned territories,
    {
        for (Territory *neighborTerritory : myTerritory->neighboringTerritories) // Look through all adjacent territories.
        {
            if (neighborTerritory->occupierName != myTerritory->occupierName)
            {
                // If an adjacent territory is owned by an enemy, add it to the set.
                temp.insert(neighborTerritory);
            }
        }
    }

    // Transfer the data to a set, and return it.
    vector<Territory *> adjacentEnemyTerritories;
    adjacentEnemyTerritories.assign(temp.begin(), temp.end());

    return adjacentEnemyTerritories; // Will need to make sure it does not get deleted.
}

// Returns a vector of all territories adjacent to those in the given vector belonging to the named player
vector<Territory *> PlayerStrategy::getAdjacentTerritoriesBelongingTo(vector<Territory *> territories, string desiredOwner)
{
    // Using a set in order to avoid duplicates.
    set<Territory *> temp;

    for (Territory *currentTerritory : territories) // for each territory in the provided vector
    {
        for (Territory *neighborTerritory : currentTerritory->neighboringTerritories) // Look through all adjacent territories.
            if (neighborTerritory->occupierName == desiredOwner)
            {
                // If an adjacent territory is owned by an enemy, add it to the set.
                temp.insert(neighborTerritory);
            }
    }

    // Transfer the data to a set, and return it.
    vector<Territory *> adjacentOwnerTerritories;
    adjacentOwnerTerritories.assign(temp.begin(), temp.end());

    return adjacentOwnerTerritories; // Will need to make sure it does not get deleted.
}

// Returns a reference to the player's most well reinforced territory.
Territory *PlayerStrategy::getStrongestTerritory()
{
    Territory *strongestTerritory;
    for (Territory *Territory : p->getOwnedTerritories())
    {
        if (Territory->numOfArmies > strongestTerritory->numOfArmies)
        {
            strongestTerritory = Territory;
        }
    }
    return strongestTerritory;
}

// Returns a reference to the player's weakest/least defended territory.
Territory *PlayerStrategy::getWeakestTerritory()
{
    Territory *weakestTerritory;
    // Set the weakestTerritory army to a high number and not 0
    weakestTerritory->numOfArmies = 1000000;

    for (Territory *Territory : p->getOwnedTerritories())
    {
        if (Territory->numOfArmies < weakestTerritory->numOfArmies)
        {
            weakestTerritory = Territory;
        }
    }
    return weakestTerritory;
}

void PlayerStrategy::reinforceTerritories(vector<Territory *> targetTerritories)
{
    int numTargetTerritories = targetTerritories.size();
    int i = 0;

    if (numTargetTerritories == 1) // If there is only one territory to reinforce, just dump the whole unit pool there.
    {
        cout << p->getPlayerName() << " wants to deploy " << p->reinforcementPool << " units on their territory " << targetTerritories.at(0)->territoryName << "." << endl;

        Order *newDeploy = new Deploy(p, p->reinforcementPool, targetTerritories.at(0));
        (*p).ordersList->addOrder(newDeploy);

        // Testing purpose only, remove later.
        // targetTerritories.at(i)->numOfArmies += p->reinforcementPool;
        // cout << targetTerritories.at(i)->territoryName << " now has " << targetTerritories.at(i)->numOfArmies << endl;
    }
    else // Else, split the number of armies by the number of territories, then assign them to each.
    {
        int troopsPerTerritory = p->reinforcementPool / numTargetTerritories; // should also be an int.
        int remainder = p->reinforcementPool % numTargetTerritories;          // the remainders goes to the first territory in the list.

        for (int i = 0; i < numTargetTerritories; i++)
        {
            int troopsToAssign = (i == 0) ? troopsPerTerritory + remainder : troopsPerTerritory;
            cout << p->getPlayerName() << " wants to deploy " << troopsToAssign << " units on their territory " << targetTerritories.at(i)->territoryName << "." << endl;

            Order *newDeploy = new Deploy(p, troopsToAssign, targetTerritories.at(i));
            (*p).ordersList->addOrder(newDeploy);

            // Testing purpose only, remove later.
            // targetTerritories.at(i)->numOfArmies += troopsToAssign;
            // cout << targetTerritories.at(i)->territoryName << " now has " << targetTerritories.at(i)->numOfArmies << endl;
        }
    }
    return;
}

void PlayerStrategy::advanceOnToDefendTerritories() // Should we check these recursively?
{
    for (Territory *territory : p->territoriesToDefend) // For every territory in territoriesToDefend,
    {
        // Loop through the neighbhoring territories.
        for (Territory *neighbor : territory->neighboringTerritories)
        {
            // If they also belong to the player,
            if (neighbor->occupier == p)
            {
                // Are not among the territoriesToDefend, and contain armies,
                auto it = std::find(p->territoriesToDefend.begin(), p->territoriesToDefend.end(), neighbor);
                if (it == p->territoriesToDefend.end() && neighbor->numOfArmies > 0)
                {
                    // Transfer the units between the two territories.
                    cout << p->getPlayerName() << " wants to move " << neighbor->numOfArmies << " units from " << neighbor->territoryName << " to " << territory->territoryName << "." << endl;

                    Order *newAdvance = new Advance(p, neighbor->numOfArmies, neighbor, territory);
                    p->ordersList->addOrder(newAdvance);
                }
            }
        }
    }
}

// Methods for the Human Player Strategy.
vector<Territory *> HumanPlayerStrategy::toAttack()
{
    // Retrieve all enemy neighboring territories
    /*vector<Territory *> enemyTerritories;
    for (auto territory : p->getOwnedTerritories())
    {
        for (auto neighbor : territory->neighboringTerritories)
        {
            if (neighbor->occupierName.compare(*(p->playerName)) != 0)
            {
                enemyTerritories.push_back(neighbor);
            }
        }
    }*/

    // Prioritize territory to attack
    return p->prioritizeTerritories(getAdjacentTerritories()); // Edited to use the getAdjacentTerritories method, which ensures the vector will not contain repeats.
    // Will need to check that it's properly created and returned as a reference.
}

vector<Territory *> HumanPlayerStrategy::toDefend()
{
    // Prioritize territory to defend
    vector<Territory *> ownedTerritories = p->getOwnedTerritories();
    return p->prioritizeTerritories(ownedTerritories);
}

bool HumanPlayerStrategy::issueOrder(bool populateVectors)
{

    // update the lists of territories to attack and defend
    if (populateVectors == true)
    {
        p->toAttack();
        p->toDefend();
    }

    // create string of players territories to defend
    string territoryStringDefend = "";
    for (int i = 0; i < p->territoriesToDefend.size(); i++)
    {
        territoryStringDefend += p->territoriesToDefend[i]->territoryName + "( " + std::to_string(i) + " ), ";
    }

    // create string of territories to attack
    string territoryStringAttack = "";
    for (int i = 0; i < p->territoriesToDefend.size(); i++)
    {
        territoryStringAttack += p->territoriesToDefend[i]->territoryName + "( " + std::to_string(i) + " ), ";
    }

    // if player has reinforcement units, they must make a Deploy order!
    if (p->reinforcementPool > 0)
    {
        // logic to create a Deploy order:
        // user enters which territory and how many units
        std::cout << "Deploy units to which territory?" << territoryStringDefend << std::endl;
        string territoryDestination;
        std::cin >> territoryDestination;
        int tIndex = std::stoi(territoryDestination);

        if (!(tIndex >= 0 && tIndex < p->territoriesToDefend.size()))
        {
            std::cout << "Invalid territory number/index" << std::endl;
        }

        std::cout << "How many units?" << std::endl;
        string units;
        std::cin >> units;
        int unitsI = std::stoi(units);

        // if the info from user checks out, make the Deploy order
        if (unitsI > 0 && unitsI <= p->getReinforcmentPool())
        {
            Order *newDeploy = new Deploy(p, unitsI, p->territoriesToDefend[tIndex]);
            (*p).ordersList->addOrder(newDeploy);
        }
        else
        {
            std::cout << "Invalid number of units (1 - units left in pool) " << std::endl;
        }
        return false;
    }
    // if no more reinforcements, player can now do advance orders or card orders
    else
    {
        // see which type of order they want to do (advance, card, or done)
        std::cout << "issue Advance order or play a card or end your turn ('advance' or 'card' or 'done')" << std::endl;
        string choice;
        std::cin >> choice;

        if (choice == "done")
        {
            return true;
        }
        // player wants to play an advance order (attack or defend)
        else if (choice == "advance")
        {
            // user enters which territories and how many units
            std::cout << "Advance units FROM which territory?" << territoryStringDefend << std::endl;
            string territorySource;
            std::cin >> territorySource;
            int tIndexS = std::stoi(territorySource);

            if (!(tIndexS >= 0 && tIndexS < p->territoriesToDefend.size()))
            {
                std::cout << "Invalid territory number/index" << std::endl;
            }

            std::cout << "Advance units TO which territory to DEFEND? (enter 'none' to see ATTACK list)" << territoryStringDefend << std::endl;
            string territoryDestination;
            std::cin >> territoryDestination;
            bool defend = true;
            int tIndexD;
            if (territoryDestination == "none")
            {
                defend = false;
                std::cout << "Advance units TO which territory to ATTACK" << territoryStringAttack << std::endl;
                string territoryDestination;
                std::cin >> territoryDestination;
                int tIndexD = std::stoi(territoryDestination);

                if (!(tIndexD >= 0 && tIndexD < p->territoriesToAttack.size()))
                {
                    std::cout << "Invalid territory number/index" << std::endl;
                }
            }
            else
            {
                int tIndexD = std::stoi(territoryDestination);

                if (!(tIndexD >= 0 && tIndexD < p->territoriesToDefend.size()))
                {
                    std::cout << "Invalid territory number/index" << std::endl;
                }
            }

            std::cout << "How many units?" << std::endl;
            string units;
            std::cin >> units;
            int unitsI = std::stoi(units);

            // if the info from user checks out, make the Advance order
            if (unitsI > 0 && unitsI <= p->territoriesToDefend[tIndexS]->numOfArmies)
            {
                if (defend)
                {
                    Order *newAdvance = new Advance(p, unitsI, p->territoriesToDefend[tIndexS], p->territoriesToDefend[tIndexD]);
                    p->ordersList->addOrder(newAdvance);
                }
                else
                {
                    Order *newAdvance = new Advance(p, unitsI, p->territoriesToDefend[tIndexS], p->territoriesToAttack[tIndexD]);
                    p->ordersList->addOrder(newAdvance);
                }
            }
            else
            {
                std::cout << "Invalid number of units (1 - units left in pool) " << std::endl;
            }
            return false;
        }
        // player wants to play a card order
        else if (choice == "card")
        {
            vector<Card *> playerCards = p->getHand()->returnMyCards();
            std::cout << "Okay, which card?\n"
                      << std::endl;
            for (Card *card : playerCards)
            {
                cout << (*card).myType << endl;
            }

            // string of card type
            string cardChoice;
            std::cin >> cardChoice;

            // remove the card from the hand
            Card *actualCard;
            for (Card *card : playerCards)
            {
                if (*(*card).myType == cardChoice)
                {
                    (*card).play();
                    p->getHand()->removeCard(card);
                    break;
                }
            }
            // play the darn card
            if (cardChoice == "bomb")
            {
                std::cout << "Bomb which territory?" << territoryStringAttack << std::endl;
                string territoryDestination;
                std::cin >> territoryDestination;
                int tIndexD = std::stoi(territoryDestination);

                if (!(tIndexD >= 0 && tIndexD < p->territoriesToAttack.size()))
                {
                    std::cout << "Invalid territory number/index" << std::endl;
                }

                Order *newBomb = new Bomb(p, p->territoriesToAttack[tIndexD]);
                p->ordersList->addOrder(newBomb);
            }
            else if (cardChoice == "airlift")
            {
                std::cout << "Airlift how many units?" << std::endl;
                string units;
                std::cin >> units;
                int howMany = std::stoi(units);

                std::cout << "From which territory?" << territoryStringDefend << std::endl;
                string territorySource;
                std::cin >> territorySource;
                int tIndexS = std::stoi(territorySource);

                if (!(tIndexS >= 0 && tIndexS < p->territoriesToDefend.size()))
                {
                    std::cout << "Invalid territory number/index" << std::endl;
                }

                std::cout << "To which territory?" << territoryStringDefend << std::endl;
                string territoryDestination;
                std::cin >> territoryDestination;
                int tIndexD = std::stoi(territoryDestination);

                if (!(tIndexD >= 0 && tIndexD < p->territoriesToDefend.size()))
                {
                    std::cout << "Invalid territory number/index" << std::endl;
                }

                Order *newAirlift = new Airlift(p, howMany, p->territoriesToDefend[tIndexS], p->territoriesToDefend[tIndexD]);
                p->ordersList->addOrder(newAirlift);
            }
            else if (cardChoice == "reinforcement")
            {
                // i made this up but let's say reinforcement means you get 3 more of them..
                p->setReinforcementPool(p->getReinforcmentPool() + 3);
            }
            else if (cardChoice == "blockade")
            {
                std::cout << "Blockade which territory" << territoryStringDefend << std::endl;
                string territoryDestination;
                std::cin >> territoryDestination;
                int tIndexD = std::stoi(territoryDestination);

                Order *newBlockade = new Blockade(p, p->territoriesToDefend[tIndexD]);
                p->ordersList->addOrder(newBlockade);
            }
            else if (cardChoice == "diplomacy")
            {
                std::cout << "Pick one of opponents territories" << territoryStringAttack << std::endl;
                string territoryDestination;
                std::cin >> territoryDestination;
                int tIndexD = std::stoi(territoryDestination);

                Order *newNegotiate = new Negotiate(p, p->territoriesToAttack[tIndexD]);
                p->ordersList->addOrder(newNegotiate);
            }
            else
            {
                std::cout << "Hmm that is not a real card" << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid choice!" << std::endl;
        }
        return false;
    }
}

// Methods for the Aggresive Player Strategy;
vector<Territory *> AggressivePlayerStrategy::toAttack()
{
    std::cout << "Aggressive player (" << p->getPlayerName() << ") is determining what territories to attack." << endl;

    vector<Territory *> enemyTerritories = getAdjacentTerritories();

    // Sort these territories by the number of troops present there.
    sort(enemyTerritories.begin(), enemyTerritories.end(), LessThan_TroopsPresent());

    // Get the first NUM_TO_ATTACK_AGGRESSIVE territories in the sorted list.
    vector<Territory *> toAttack;

    if (enemyTerritories.size() > NUM_TO_ATTACK_AGGRESSIVE) // Only do this fancy copy/splicing stuff if the list of adjacent enemy territories is longer than NUM_TO_ATTACK_AGGRESSIVE.
    {
        // The most vulnerable territories should be at the start of the list.
        toAttack.assign(enemyTerritories.begin(), enemyTerritories.begin() + NUM_TO_ATTACK_AGGRESSIVE);
    }
    // Else, just return a copy of it.
    else
        toAttack = enemyTerritories;

    return toAttack;
}

vector<Territory *> AggressivePlayerStrategy::toDefend()
{
    std::cout << "Aggressive player (" << p->getPlayerName() << ") is determining what territories to defend." << endl;

    // Collect the potential territories to reinforce.
    vector<Territory *> candidateTerritories = getAdjacentTerritoriesBelongingTo(p->territoriesToAttack, p->getPlayerName());

    // Sort these territories by the number of troops present there.
    sort(candidateTerritories.begin(), candidateTerritories.end(), LessThan_TroopsPresent_SurroundingEnemies());

    // Get the last NUM_TO_DEFEND_AGGRESIVE territories in the sorted list.
    vector<Territory *> toDefend;

    if (candidateTerritories.size() > NUM_TO_DEFEND_AGGRESIVE) // Only do this fancy copy/splicing stuff if the list of adjacent enemy territories is longer than NUM_TO_DEFEND_AGGRESIVE.
    {
        // The most vulnerable territories should be at the start of the list.
        toDefend.assign(candidateTerritories.end() - NUM_TO_DEFEND_AGGRESIVE, candidateTerritories.end());
    }
    // Else, just return a copy of it.
    else
        toDefend = candidateTerritories;

    return toDefend;
}

bool AggressivePlayerStrategy::issueOrder(bool populateVectors)
{   

    // Do we call toAttack and toDefend here?
    if (populateVectors == true)
    {
        p->toAttack();
        p->toDefend();
    }

    if (p->reinforcementPool > 0)
    {
        cout << p->getPlayerName() << " has " << p->reinforcementPool << " troops to deploy." << endl;
        // Reinforce the territories in toDefend();
        reinforceTerritories(p->territoriesToDefend);
    }

    // If possible, move adjacent troops to the territories in territoriesToDefend.
    advanceOnToDefendTerritories();

    // Advance on the territories in territoriesToAttack.
    for (Territory *enemyTerritory : p->territoriesToAttack) // For every territory in territoriesToAttack,
    {
        // Loop through the neighbhoring territories.
        for (Territory *territory : enemyTerritory->neighboringTerritories)
        {
            // If they also belong to the player and contain armies,
            if (territory->occupier == p && territory->numOfArmies > 0)
            {
                // Attack the enemy territory.
                cout << p->getPlayerName() << " wants to send " << territory->numOfArmies << " units from " << territory->territoryName << " to attack " << enemyTerritory->territoryName << ", belonging to " << enemyTerritory->occupierName << "." << endl;

                Order *newAdvance = new Advance(p, territory->numOfArmies, territory, enemyTerritory);
                p->ordersList->addOrder(newAdvance);
                // We might however end up with contradictory orders, sending the same troops to different territories.
            }
        }
    }

    // Use aggressive cards.
    for (Card *card : p->getHand()->returnMyCards())
    {
        // Look for a card of an accepted type,
        if (*(card->myType) == "bomb") // Is any other card type valid?
        {
            // Use the card on a random territoryToAttack();

            std::srand(static_cast<unsigned int>(std::time(nullptr))); // init the random number generator
            int i = std::rand() % (p->territoriesToAttack.size());     // Generate a random index.

            cout << p->getPlayerName() << " wants to bomb " << p->territoriesToAttack[i]->territoryName << ", belonging to " << p->territoriesToAttack[i]->occupierName << "." << endl;

            Order *newBomb = new Bomb(p, p->territoriesToAttack[i]);
            p->ordersList->addOrder(newBomb);

            break; // Should break us out of the loop.
        }

        // Reinforcement (we're not sure what this actually does :x)
    }

    return true;
}

// Methods for the Benevolent Player Strategy;
vector<Territory *> BenevolentPlayerStrategy::toAttack()
{
    std::cout << "Benevolent player (" << p->getPlayerName() << ") is determining what territories to attack." << endl;

    // Returns an empty toAttack vector so that no one will be attacked.
    vector<Territory *> toAttack;
    return toAttack;
}

vector<Territory *> BenevolentPlayerStrategy::toDefend()
{
    std::cout << "Benevolent player (" << p->getPlayerName() << ") is determining what territories to defend." << endl;

    vector<Territory *> ownedTerritories = p->getOwnedTerritories();

    // Sort the player's territories by the number of adjacent enemy troops, then the number of their own units present on them.
    sort(ownedTerritories.begin(), ownedTerritories.end(), LessThan_AdjacentEnemyTroops_TroopsPresent());

    // Get the last NUM_TO_DEFEND territories in the sorted list.
    vector<Territory *> toDefend;

    if (ownedTerritories.size() > NUM_TO_DEFEND_DEFENSIVE) // Only do this fancy copy/splicing stuff if the list of owned territories is longer than NUM_TO_DEFEND.
    {
        // The most vulnerable territories should be at the end of the list.
        toDefend.assign(ownedTerritories.end() - NUM_TO_DEFEND_DEFENSIVE, ownedTerritories.end());
    }
    // Else, just return a copy of it.
    else
        toDefend = ownedTerritories;

    return toDefend;
}

bool BenevolentPlayerStrategy::issueOrder(bool populateVectors)
{

    if (populateVectors == true)
    {
        p->toAttack();
        p->toDefend();
    }

    // If possible, reinforce the territories in toDefend();
    if (p->reinforcementPool > 0)
    {
        cout << p->getPlayerName() << " has " << p->reinforcementPool << " troops to deploy." << endl;
        reinforceTerritories(p->territoriesToDefend);
    }

    // If possible, move adjacent troops to the territories in toDefend();
    advanceOnToDefendTerritories();

    // The benevolent player does not attack.

    // Which are the nonviolent card? Airlift, reinforcement, blockade, diplomacy?
    for (Card *card : p->getHand()->returnMyCards())
    {
        // Look for a card of an accepted type...

        // Diplomacy
        if (*(card->myType) == "diplomacy")
        {
            // Finc a valid diplomacy target.
            Territory* target = nullptr;
            for (Territory* territory : p->territoriesToDefend)
            {
                for (Territory* neighbor : territory->neighboringTerritories)
                {
                    if (territory->occupier != neighbor->occupier)
                    {
                        // Any neighborhing enemy is a valid target.
                        target = neighbor;
                        break;
                    }
                }
            }

            if (target != nullptr) // Safety measures. Don't try to use the card if no target was found.
            {
                cout << p->getPlayerName() << " wants to negotiate with " << target->occupierName << "." << endl;

                Order* newNegotiate = new Negotiate(p, target);
                p->ordersList->addOrder(newNegotiate);

                break;
            }
        }

        // Blockade
        if (*(card->myType) == "blockade")
        {
            vector<Territory*> ownedTerritories = p->getOwnedTerritories();
            
            // Do not perform the blockade if too few territories are owned.
            if (ownedTerritories.size() > NUM_TO_DEFEND_DEFENSIVE)
            {
                // Look for the more vulnerable territory in order to blockade it.
                sort(ownedTerritories.begin(), ownedTerritories.end(), LessThan_AdjacentEnemyTroops_TroopsPresent());

                // Don't give away a territory in territoriesToDefend().
                for (int i = ownedTerritories.size() - 1; i >= 0; i--)
                {
                    auto it = std::find(p->territoriesToDefend.begin(), p->territoriesToDefend.end(), ownedTerritories.at(i));
                    if (it == p->territoriesToDefend.end())
                    {
                        Territory* target = ownedTerritories.at(i);
                        
                        cout << p->getPlayerName() << " wants to blockade their territory " << target->territoryName << "." << endl;

                        Order* newBlockade = new Blockade(p, target);
                        p->ordersList->addOrder(newBlockade);

                        break;
                    }
                }
            }
        }

        if (*(card->myType) == "airlift")
        {
            vector<Territory*> ownedTerritories = p->getOwnedTerritories();

            // Only check for potential airlifts if territories exist outsde of territoriesToDefend.
            if (ownedTerritories.size() > NUM_TO_DEFEND_DEFENSIVE)
            {
                // Look for a 'safe' territory where troops are present.
                // Start with the territories surrounded by fewer enemy troops.
                sort(ownedTerritories.begin(), ownedTerritories.end(), LessThan_AdjacentEnemyTroops());

                for (int i = 0; i < ownedTerritories.size(); i++)
                {
                    // Don't take troops away from territories to defend.
                    auto it = std::find(p->territoriesToDefend.begin(), p->territoriesToDefend.end(), ownedTerritories.at(i));
                    if (it == p->territoriesToDefend.end())
                    {
                        std::srand(static_cast<unsigned int>(std::time(nullptr))); // init the random number generator
                        int j = std::rand() % (p->territoriesToDefend.size()); // Generate a random index.

                        Territory* source = ownedTerritories.at(i);
                        Territory* target = p->territoriesToDefend.at(j);

                        cout << p->getPlayerName() << " wants to airlift " << source->numOfArmies << " units from " << source->territoryName << " to " << target->territoryName << "." << endl;

                        Order* newAirlift = new Airlift(p, source->numOfArmies, source, target);
                        p->ordersList->addOrder(newAirlift);

                        break;
                    }
                }
            }
        }

        // Reinforcement (we're not sure what this actually does :x)
    }

    return true;
}

// Methods for the Neutral Player Strategy;
vector<Territory *> NeutralPlayerStrategy::toAttack()
{
    std::cout << "Neutral player (" << p->getPlayerName() << ") is determining what territories to attack." << endl;

    // Returns an empty toAttack vector so that no one will be attacked.
    vector<Territory *> toAttack;
    return toAttack;
}

vector<Territory *> NeutralPlayerStrategy::toDefend()
{
    std::cout << "Neutral player (" << p->getPlayerName() << ") is determining what territories to defend." << endl;

    // Returns an empty toDefend vector so that no territory will be defended.
    vector<Territory *> toDefend;
    return toDefend;
}
// issueOrder() that does nothing.
bool NeutralPlayerStrategy::issueOrder(bool populateVectors)
{

    // Not actually needed.
    /*if (populateVectors == true)
    {
        p->toAttack();
        p->toDefend();
    }*/

    // The neutral player doesn't do shit.

    // Check the total number of troops that the player has across all territories. If that number diminishes, meaning the player got attacked, the neutral player becomes aggressive.

    return true;
}

// Methods for the Cheater Player Strategy;
vector<Territory *> CheaterPlayerStrategy::toAttack()
{
    std::cout << "Cheater player (" << p->getPlayerName() << ") is determining what territories to attack." << endl;

    // Collect the list of adjacent enemy territories. They will all be attacked!
    vector<Territory *> toAttack = getAdjacentTerritories();
    return toAttack;
}

vector<Territory *> CheaterPlayerStrategy::toDefend()
{
    std::cout << "Cheater player (" << p->getPlayerName() << ") is determining what territories to defend." << endl;

    // Returns an empty toDefend vector so that no territory will be defended.
    vector<Territory *> toDefend;
    return toDefend;
}

// The Cheater Player issueOrder does not do anything, since it conquers nearby territories no matter what
bool CheaterPlayerStrategy::issueOrder(bool populateVectors)
{

    if (populateVectors == true)
    {
        p->toAttack();
        p->toDefend(); // Will be empty.
    }

    // No issueOrder method since the cheater player does not use cards!!!

    // Auto conquer the territories in toAttack. Should this be done as an order??
    for (Territory *territory : p->territoriesToAttack)
    {
        cout << "The cheater player has captured " << territory->territoryName << " from " << territory->occupier->getPlayerName() << "." << endl;

        territory->occupier->removeOwnedTerritory(territory);
        p->addOwnedTerritory(territory);
    }

    return true;
}

// Utility methods and structs.

// Used to sort a vector of territories by the number of troops present on them.
inline bool LessThan_TroopsPresent::operator()(const Territory *A, const Territory *B)
{
    // The more units present on a territory, the higher it is sorted.
    return (A->numOfArmies < B->numOfArmies);
}

// Used to stort a vector of territories by the number of enemy territories surrounding them.
inline bool LessTan_SurroundingEnemies::operator()(const Territory *A, const Territory *B)
{
    // Count the number of surrounding enemy territories.
    int surroundingEnemyTerritoriesA = 0;
    int surroundingEnemyTerritoriesB = 0;

    for (const Territory *neighborA : A->neighboringTerritories)
    {
        if (neighborA->occupierName != A->occupierName)
        {
            surroundingEnemyTerritoriesA++;
        }
    }
    for (const Territory *neighborB : B->neighboringTerritories)
    {
        if (neighborB->occupierName != B->occupierName)
        {
            surroundingEnemyTerritoriesB++;
        }
    }

    // The more surrounding enemy territories, the higher the territory is sorted.
    return (surroundingEnemyTerritoriesA < surroundingEnemyTerritoriesB);
}

// Used to sort a vector of territories by the number of enemy territories surrounding them, then the number of troops present on them.
inline bool LessThan_TroopsPresent_SurroundingEnemies::operator()(const Territory *A, const Territory *B)
{
    // Priorize the number of troops present over the number of adjacent enemy territories.
    if (A->numOfArmies != B->numOfArmies)
        // The more units present on a territory, the higher it is sorted.
        return (A->numOfArmies < B->numOfArmies);

    // Count the number of surrounding enemy territories.
    int surroundingEnemyTerritoriesA = 0;
    int surroundingEnemyTerritoriesB = 0;

    for (const Territory *neighborA : A->neighboringTerritories)
    {
        if (neighborA->occupierName != A->occupierName)
        {
            surroundingEnemyTerritoriesA++;
        }
    }
    for (const Territory *neighborB : B->neighboringTerritories)
    {
        if (neighborB->occupierName != B->occupierName)
        {
            surroundingEnemyTerritoriesB++;
        }
    }

    // The more surrounding enemy territories, the higher the territory is sorted.
    return (surroundingEnemyTerritoriesA < surroundingEnemyTerritoriesB);
}

// Used to sort a vector of territories by the number of adjacent enemy troops.
inline bool LessThan_AdjacentEnemyTroops::operator()(const Territory *A, const Territory *B)
{
    // Count the number of surrounding enemy troops.
    int surroundingEnemyTroopsA = 0;
    int surroundingEnemyTroopsB = 0;

    for (const Territory *neighborA : A->neighboringTerritories)
    {
        if (neighborA->occupierName != A->occupierName)
        {
            surroundingEnemyTroopsA += neighborA->numOfArmies;
        }
    }
    for (const Territory *neighborB : B->neighboringTerritories)
    {
        if (neighborB->occupierName != B->occupierName)
        {
            surroundingEnemyTroopsB += neighborB->numOfArmies;
        }
    }

    // The more surrounding enemy troops, the higher a territory is sorted.
    return (surroundingEnemyTroopsA < surroundingEnemyTroopsB);
}

// Used to sort a vector of territories by the number of adjacent enemy troops, then the number of one's own units present on them.
inline bool LessThan_AdjacentEnemyTroops_TroopsPresent::operator()(const Territory *A, const Territory *B)
{
    // Count the number of surrounding enemy troops.
    int surroundingEnemyTroopsA = 0;
    int surroundingEnemyTroopsB = 0;

    for (const Territory *neighborA : A->neighboringTerritories)
    {
        if (neighborA->occupierName != A->occupierName)
        {
            surroundingEnemyTroopsA += neighborA->numOfArmies;
        }
    }
    for (const Territory *neighborB : B->neighboringTerritories)
    {
        if (neighborB->occupierName != B->occupierName)
        {
            surroundingEnemyTroopsB += neighborB->numOfArmies;
        }
    }

    // Priorize the number of surrounding enemy troops over that of owned troops.
    if (surroundingEnemyTroopsA != surroundingEnemyTroopsB)
        // The more surrounding enemy troops, the higher a territory is sorted.
        return (surroundingEnemyTroopsA < surroundingEnemyTroopsB);

    // If both territories are surrounded by the same number of enemy troops, compare their own unit numbers.
    // The fewer units present, the higher a territory is sorted.
    return (A->numOfArmies > B->numOfArmies);
}
