#include "PlayerStrategy.h"

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



// Methods for the Human Player Strategy.

// Methods for the Aggresive Player Strategy;
vector<Territory *> AggressivePlayerStrategy::toAttack()
{
    // Collect the list of adjacent enemy territories.
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
    // Returns an empty toDefend vector so that no territory will be defended?
    vector<Territory *> toDefend;
    return toDefend;

    // Use LessThan_TroopsPresent_SurroundingEnemies sorting instead?
    // Go on to defend territories that are already strong, but likely to be attacked?
}

void AggressivePlayerStrategy::issueOrder(Order *o)
{
}


// Methods for the Benevolent Player Strategy;
vector<Territory *> BenevolentPlayerStrategy::toAttack()
{
    // Returns an empty toAttack vector so that no one will be attacked.
    vector<Territory *> toAttack;
    return toAttack;
}

vector<Territory *> BenevolentPlayerStrategy::toDefend()
{
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
}


// Methods for the Neutral Player Strategy;
vector<Territory *> NeutralPlayerStrategy::toAttack()
{
    // Returns an empty toAttack vector so that no one will be attacked.
    vector<Territory *> toAttack;
    return toAttack;
}

vector<Territory *> NeutralPlayerStrategy::toDefend()
{
    // Returns an empty toDefend vector so that no territory will be defended.
    vector<Territory *> toDefend;
    return toDefend;
}
// issueOrder() that does nothing.
void NeutralPlayerStrategy::issueOrder(Order *o)
{
    return;
}
// How to detect when it is attacked?


void NeutralPlayerStrategy::issueOrder(Order *o)
{
    // Check the total number of troops that the player has across all territories. If that number diminishes, meaning the player got attacked, the neutral player becomes aggressive
}


// Methods for the Cheater Player Strategy;
vector<Territory *> CheaterPlayerStrategy::toAttack()
{
    // Collect the list of adjacent enemy territories. They will all be attacked!
    vector<Territory *> toAttack = getAdjacentTerritories();
    return toAttack;
}

// No issueOrder method since the cheater player does not use cards!!!
void CheaterPlayerStrategy::issueOrder(Order* o)
{
    return;
}



// Utility methods and structs.

// Used to sort a vector of territories by the number of troops present on them.
inline bool LessThan_TroopsPresent::operator()(const Territory &A, const Territory &B)
{
    // The more units present on a territory, the higher it is sorted.
    return (A.numOfArmies < B.numOfArmies);
}

// Used to stort a vector of territories by the number of enemy territories surrounding them.
inline bool LessTan_SurroundingEnemies::operator()(const Territory &A, const Territory &B)
{
    // Count the number of surrounding enemy territories.
    int surroundingEnemyTerritoriesA = 0;
    int surroundingEnemyTerritoriesB = 0;

    for (const Territory *neighborA : A.neighboringTerritories)
    {
        if (neighborA->occupierName != A.occupierName)
        {
            surroundingEnemyTerritoriesA++;
        }
    }
    for (const Territory *neighborB : B.neighboringTerritories)
    {
        if (neighborB->occupierName != B.occupierName)
        {
            surroundingEnemyTerritoriesB++;
        }
    }

    // The more surrounding enemy territories, the higher the territory is sorted.
    return (surroundingEnemyTerritoriesA < surroundingEnemyTerritoriesB);
}

// Used to sort a vector of territories by the number of enemy territories surrounding them, then the number of troops present on them.
inline bool LessThan_TroopsPresent_SurroundingEnemies::operator()(const Territory &A, const Territory &B)
{
    // Priorize the number of troops present over the number of adjacent enemy territories.
    if (A.numOfArmies != B.numOfArmies)
        // The more units present on a territory, the higher it is sorted.
        return (A.numOfArmies < B.numOfArmies);

    // Count the number of surrounding enemy territories.
    int surroundingEnemyTerritoriesA = 0;
    int surroundingEnemyTerritoriesB = 0;

    for (const Territory *neighborA : A.neighboringTerritories)
    {
        if (neighborA->occupierName != A.occupierName)
        {
            surroundingEnemyTerritoriesA++;
        }
    }
    for (const Territory *neighborB : B.neighboringTerritories)
    {
        if (neighborB->occupierName != B.occupierName)
        {
            surroundingEnemyTerritoriesB++;
        }
    }

    // The more surrounding enemy territories, the higher the territory is sorted.
    return (surroundingEnemyTerritoriesA < surroundingEnemyTerritoriesB);
}

// Used to sort a vector of territories by the number of adjacent enemy troops.
inline bool LessThan_AdjacentEnemyTroops::operator()(const Territory &A, const Territory &B)
{
    // Count the number of surrounding enemy troops.
    int surroundingEnemyTroopsA = 0;
    int surroundingEnemyTroopsB = 0;

    for (const Territory *neighborA : A.neighboringTerritories)
    {
        if (neighborA->occupierName != A.occupierName)
        {
            surroundingEnemyTroopsA += neighborA->numOfArmies;
        }
    }
    for (const Territory *neighborB : B.neighboringTerritories)
    {
        if (neighborB->occupierName != B.occupierName)
        {
            surroundingEnemyTroopsB += neighborB->numOfArmies;
        }
    }

    // The more surrounding enemy troops, the higher a territory is sorted.
    return (surroundingEnemyTroopsA < surroundingEnemyTroopsB);
}

// Used to sort a vector of territories by the number of adjacent enemy troops, then the number of one's own units present on them.
inline bool LessThan_AdjacentEnemyTroops_TroopsPresent::operator()(const Territory &A, const Territory &B)
{
    // Count the number of surrounding enemy troops.
    int surroundingEnemyTroopsA = 0;
    int surroundingEnemyTroopsB = 0;

    for (const Territory *neighborA : A.neighboringTerritories)
    {
        if (neighborA->occupierName != A.occupierName)
        {
            surroundingEnemyTroopsA += neighborA->numOfArmies;
        }
    }
    for (const Territory *neighborB : B.neighboringTerritories)
    {
        if (neighborB->occupierName != B.occupierName)
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
    return (A.numOfArmies > B.numOfArmies);
}
