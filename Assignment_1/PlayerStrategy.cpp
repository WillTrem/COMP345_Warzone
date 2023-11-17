#include "PlayerStrategy.h"

// Abstract strategy class

// Human Player Strategy.
// "Requires user interactions to make decisions, including deploy and advance orders, as well as playing any card."



// Utility methods and structs.

// Used to sort a vector of territories by the number of troops present on them.
inline bool LessThan_TroopsPresent::operator() (const Territory& A, const Territory& B)
{
	// The more units present on a territory, the higher it is sorted.
	return (A.numOfArmies < B.numOfArmies);
}

// Used to stort a vector of territories by the number of enemy territories surrounding them.
inline bool LessTan_SurroundingEnemies::operator() (const Territory& A, const Territory& B)
{
	// Count the number of surrounding enemy territories.
	int surroundingEnemyTerritoriesA = 0;
	int surroundingEnemyTerritoriesB = 0;

	for (const Territory* neighborA : A.neighboringTerritories)
	{
		if (neighborA->occupierName != A.occupierName)
		{
			surroundingEnemyTerritoriesA++;
		}
	}
	for (const Territory* neighborB : B.neighboringTerritories)
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
inline bool LessThan_TroopsPresent_SurroundingEnemies::operator() (const Territory& A, const Territory& B)
{
	// Priorize the number of troops present over the number of adjacent enemy territories.
	if (A.numOfArmies != B.numOfArmies)
		// The more units present on a territory, the higher it is sorted.
		return (A.numOfArmies < B.numOfArmies);
	
	// Count the number of surrounding enemy territories.
	int surroundingEnemyTerritoriesA = 0;
	int surroundingEnemyTerritoriesB = 0;

	for (const Territory* neighborA : A.neighboringTerritories)
	{
		if (neighborA->occupierName != A.occupierName)
		{
			surroundingEnemyTerritoriesA++;
		}
	}
	for (const Territory* neighborB : B.neighboringTerritories)
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
inline bool LessThan_AdjacentEnemyTroops::operator() (const Territory& A, const Territory& B)
{
	// Count the number of surrounding enemy troops.
	int surroundingEnemyTroopsA = 0;
	int surroundingEnemyTroopsB = 0;

	for (const Territory* neighborA : A.neighboringTerritories)
	{
		if (neighborA->occupierName != A.occupierName)
		{
			surroundingEnemyTroopsA += neighborA->numOfArmies;
		}
	}
	for (const Territory* neighborB : B.neighboringTerritories)
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
inline bool LessThan_AdjacentEnemyTroops_TroopsPresent::operator() (const Territory& A, const Territory& B)
{
	// Count the number of surrounding enemy troops.
	int surroundingEnemyTroopsA = 0;
	int surroundingEnemyTroopsB = 0;

	for (const Territory* neighborA : A.neighboringTerritories)
	{
		if (neighborA->occupierName != A.occupierName)
		{
			surroundingEnemyTroopsA += neighborA->numOfArmies;
		}
	}
	for (const Territory* neighborB : B.neighboringTerritories)
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