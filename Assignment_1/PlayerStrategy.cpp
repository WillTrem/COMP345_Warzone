// REMINDER TO SELF: MAKE FUNCTION TO FIND STRONGEST AND WEAKEST COUNTRIES!!!!
// REMINDER TO SELF: MAKE FUNCTION TO FIND STRONGEST AND WEAKEST COUNTRIES!!!!
// REMINDER TO SELF: MAKE FUNCTION TO FIND STRONGEST AND WEAKEST COUNTRIES!!!!
// REMINDER TO SELF: MAKE FUNCTION TO FIND STRONGEST AND WEAKEST COUNTRIES!!!!
// REMINDER TO SELF: MAKE FUNCTION TO FIND STRONGEST AND WEAKEST COUNTRIES!!!!
// REMINDER TO SELF: MAKE FUNCTION TO FIND STRONGEST AND WEAKEST COUNTRIES!!!!
// REMINDER TO SELF: MAKE FUNCTION TO FIND STRONGEST AND WEAKEST COUNTRIES!!!!
// REMINDER TO SELF: MAKE FUNCTION TO FIND STRONGEST AND WEAKEST COUNTRIES!!!!
// REMINDER TO SELF: MAKE FUNCTION TO FIND STRONGEST AND WEAKEST COUNTRIES!!!!

#include "PlayerStrategy.h"
const int NUM_TO_ATTACK = 5;
const int NUM_TO_DEFEND = 5;

PlayerStrategy::PlayerStrategy()
{
    // Implementation if needed
}

AggressivePlayerStrategy::AggressivePlayerStrategy()
{
    // Implementation if needed
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy()
{
    // Implementation if needed
}

NeutralPlayerStrategy::NeutralPlayerStrategy()
{
    // Implementation if needed
}

CheaterPlayerStrategy::CheaterPlayerStrategy()
{
    // Implementation if needed
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

// Methods for the Human Player Strategy.
vector<Territory *> HumanPlayerStrategy::toAttack()
{
    // We could use the method in PlayerStrategy for this, which ensures there are no repeats in the vector?
    // Retrieve all enemy neighboring territories
    vector<Territory *> enemyTerritories;
    for (auto territory : p->getOwnedTerritories())
    {
        for (auto neighbor : territory->neighboringTerritories)
        {
            if (neighbor->occupierName.compare(*(p->playerName)) != 0)
            {
                enemyTerritories.push_back(neighbor);
            }
        }
    }

    // Prioritize territory to attack
    return p->prioritizeTerritories(enemyTerritories);
}

vector<Territory *> HumanPlayerStrategy::toDefend()
{
    // Prioritize territory to defend
    vector<Territory *> ownedTerritories = p->getOwnedTerritories();
    return p->prioritizeTerritories(ownedTerritories);
}

// TODO
void HumanPlayerStrategy::issueOrder(Order *o)
{
    p->getOrdersList()->addOrder(o);
}

// Methods for the Aggresive Player Strategy;
vector<Territory *> AggressivePlayerStrategy::toAttack()
{
    std::cout << "Aggressive player is attacking" << endl;

    vector<Territory *> enemyTerritories = getAdjacentTerritories();

    // Sort these territories by the number of troops present there.
    sort(enemyTerritories.begin(), enemyTerritories.end(), LessThan_TroopsPresent());

    // Get the first NUM_TO_DEFEND territories in the sorted list.
    vector<Territory *> toAttack;

    if (enemyTerritories.size() > NUM_TO_ATTACK) // Only do this fancy copy/splicing stuff if the list of adjacent enemy territories is longer than NUM_TO_DEFEND.
    {
        // The most vulnerable territories should be at the start of the list.
        toAttack.assign(enemyTerritories.begin(), enemyTerritories.begin() + NUM_TO_ATTACK);
    }
    // Else, just return a copy of it.
    else
        toAttack = enemyTerritories;

    return toAttack;
}

vector<Territory *> AggressivePlayerStrategy::toDefend()
{
    std::cout << "Aggressive player is defending" << endl;

    // Returns an empty toDefend vector so that no territory will be defended?
    vector<Territory *> toDefend;
    return toDefend;

    // Use LessThan_TroopsPresent_SurroundingEnemies sorting instead?
    // Go on to defend territories that are already strong, but likely to be attacked?
}

void AggressivePlayerStrategy::issueOrder(Order *o)
{
    // Check if 'o' is a Deploy object
    if (Deploy *deployOrder = dynamic_cast<Deploy *>(o))
    {
        // Find the strongest country
        Territory *strongest = getStrongestTerritory();
        Deploy(p, p->getReinforcmentPool(), strongest);
    }

    // Check if 'o' is a Advance object
    if (Advance *advanceOrder = dynamic_cast<Advance *>(o))
    {
        // Brainstorm about the advance recursively
        // for ();
    }

    // Check if 'o' is a Bomb object
    if (Bomb *bombOrder = dynamic_cast<Bomb *>(o))
    {
        Territory *aboutToGetBombed = getAdjacentTerritories()[0];
        Bomb(p, aboutToGetBombed);
    }
}

// Methods for the Benevolent Player Strategy;
vector<Territory *> BenevolentPlayerStrategy::toAttack()
{
    std::cout << "Benelovent player is attacking" << endl;

    // Returns an empty toAttack vector so that no one will be attacked.
    vector<Territory *> toAttack;
    return toAttack;
}

vector<Territory *> BenevolentPlayerStrategy::toDefend()
{
    std::cout << "Benelovent player is defending" << endl;

    // Sort the player's territories by the number of adjacent enemy troops, then the number of their own units present on them.
    sort(p->getOwnedTerritories().begin(), p->getOwnedTerritories().end(), LessThan_AdjacentEnemyTroops_TroopsPresent());

    // Get the last NUM_TO_DEFEND territories in the sorted list.
    vector<Territory *> toDefend;

    if (p->getOwnedTerritories().size() > NUM_TO_DEFEND) // Only do this fancy copy/splicing stuff if the list of owned territories is longer than NUM_TO_DEFEND.
    {
        // The most vulnerable territories should be at the end of the list.
        toDefend.assign(p->getOwnedTerritories().end() - NUM_TO_DEFEND, p->getOwnedTerritories().end());
    }
    // Else, just return a copy of it.
    else
        toDefend = p->getOwnedTerritories();

    return toDefend;
}

void BenevolentPlayerStrategy::issueOrder(Order *o)
{
    // Deploy troops to own territories.
    // Move troops to weaker territories when possible?
    // Only play nonviolent cards.

    // Check if 'o' is a Deploy object
    if (Deploy *deployOrder = dynamic_cast<Deploy *>(o))
    {
        // Find the weakest territory
        Territory *weakest = getWeakestTerritory();
        Deploy(p, p->getReinforcmentPool(), weakest);
    }

    // Check if 'o' is a Airlift object
    if (Airlift *airliftOrder = dynamic_cast<Airlift *>(o))
    {
        // Find the weakest territory
        Territory *weakest = getWeakestTerritory();
        Airlift(p, p->getReinforcmentPool(), weakest);
    }

    // Check if 'o' is a Blockade object
    if (Blockade *blockadeOrder = dynamic_cast<Blockade *>(o))
    {
        Territory *aboutToGetBombed = getAdjacentTerritories()[0];
        Bomb(p, aboutToGetBombed);
    }
}

// Methods for the Neutral Player Strategy;
vector<Territory *> NeutralPlayerStrategy::toAttack()
{
    std::cout << "Neutral player is attacking" << endl;

    // Returns an empty toAttack vector so that no one will be attacked.
    vector<Territory *> toAttack;
    return toAttack;
}

vector<Territory *> NeutralPlayerStrategy::toDefend()
{
    std::cout << "Neutral player is defending" << endl;

    // Returns an empty toDefend vector so that no territory will be defended.
    vector<Territory *> toDefend;
    return toDefend;
}
// issueOrder() that does nothing.
void NeutralPlayerStrategy::issueOrder(Order *o)
{
    // Check the total number of troops that the player has across all territories. If that number diminishes, meaning the player got attacked, the neutral player becomes aggressive
    return;
}

// Methods for the Cheater Player Strategy;
vector<Territory *> CheaterPlayerStrategy::toAttack()
{
    std::cout << "Cheater player is attacking" << endl;

    // Collect the list of adjacent enemy territories. They will all be attacked!
    vector<Territory *> toAttack = getAdjacentTerritories();
    return toAttack;
}

vector<Territory *> CheaterPlayerStrategy::toDefend()
{
    std::cout << "Cheater player is defending" << endl;

    // Returns an empty toDefend vector so that no territory will be defended.
    vector<Territory *> toDefend;
    return toDefend;
}

// The Cheater Player issueOrder does not do anything, since it conquers nearby territories no matter what
void CheaterPlayerStrategy::issueOrder(Order *o)
{
    // No issueOrder method since the cheater player does not use cards!!!

    // Auto conquer the territories in toAttack?

    return;
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
