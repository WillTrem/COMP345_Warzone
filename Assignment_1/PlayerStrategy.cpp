#include "PlayerStrategy.h"


// Constants.
const int NUM_TO_ATTACK = 5;
const int NUM_TO_DEFEND = 5;

const int NUM_TO_ATTACK_AGGRESSIVE = 3;
const int NUM_TO_DEFEND_AGGRESIVE = 1;


// Constructors.
PlayerStrategy::PlayerStrategy(Player* player)
{
    p = player;
    cout << "\nAssigned a player strategy to " << p->getPlayerName() << endl;
}

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) : PlayerStrategy(player)
{
    // Implementation if needed
    cout << "It is the Human player strategy." << endl;
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player)
{
    // Implementation if needed
    cout << "It is the Aggresive player strategy." << endl;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player)
{
    // Implementation if needed
    cout << "It is the Benevolent player strategy." << endl;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player)
{
    // Implementation if needed
    cout << "It is the Neutral player strategy." << endl;
}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) : PlayerStrategy(player)
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
vector<Territory*> PlayerStrategy::getAdjacentTerritoriesBelongingTo(vector<Territory*> territories, string desiredOwner)
{
    // Using a set in order to avoid duplicates.
    set<Territory*> temp;

    for (Territory* currentTerritory : territories) // for each territory in the provided vector
    {
        for (Territory* neighborTerritory : currentTerritory->neighboringTerritories) // Look through all adjacent territories. 
            if (neighborTerritory->occupierName == desiredOwner)
            {
                // If an adjacent territory is owned by an enemy, add it to the set.
                temp.insert(neighborTerritory);
            }
    }

    // Transfer the data to a set, and return it.
    vector<Territory*> adjacentOwnerTerritories;
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

void PlayerStrategy::reinforceTerritories(vector<Territory*> targetTerritories)
{
    int numTargetTerritories = targetTerritories.size();
    int i = 0;

    if (numTargetTerritories == 1) // If there is only one territory to reinforce, just dump the whole unit pool there.
    {
        targetTerritories.at(0)->numOfArmies += p->reinforcementPool;
        cout << p->getPlayerName() << " has deployed " << p->reinforcementPool << " units on their territory " << targetTerritories.at(0)->territoryName << "." << endl;

        p->reinforcementPool = 0;

        // To do: switch this to issuing actual order objects.
    }
    else // Else, loop through the territories listed and assign armies until the pool is empty.
    {
        while (p->reinforcementPool > 0)
        {
            targetTerritories.at(i)->numOfArmies++;
            cout << p->getPlayerName() << " has deployed a unit on their territory " << targetTerritories.at(i)->territoryName << "." << endl;

            p->reinforcementPool--;
            i = (i + 1) % numTargetTerritories;
        }
    }
    return;
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
			Order* newDeploy = new Deploy(p, unitsI, p->territoriesToDefend[tIndex]);
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
					Order* newAdvance = new Advance(p, unitsI, p->territoriesToDefend[tIndexS], p->territoriesToDefend[tIndexD]);
					p->ordersList->addOrder(newAdvance);
				}
				else
				{
					Order* newAdvance = new Advance(p, unitsI, p->territoriesToDefend[tIndexS], p->territoriesToAttack[tIndexD]);
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
			vector<Card*> playerCards = p->getHand()->returnMyCards();
			std::cout << "Okay, which card?\n" << std::endl;
			for (Card *card : playerCards)
			{
				cout << (*card).myType << endl;
			}
			
			// string of card type
			string cardChoice;
			std::cin >> cardChoice;

			// remove the card from the hand
			Card* actualCard;
			for (Card *card : playerCards)
			{	
				if ((*card).myType == cardChoice)
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

				Order* newBomb = new Bomb(p, p->territoriesToAttack[tIndexD]);
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

				Order* newAirlift = new Airlift(p, howMany, p->territoriesToDefend[tIndexS], p->territoriesToDefend[tIndexD]);
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

				Order* newBlockade = new Blockade(p, p->territoriesToDefend[tIndexD]);
				p->ordersList->addOrder(newBlockade);
			}
			else if (cardChoice == "diplomacy")
			{
				std::cout << "Pick one of opponents territories" << territoryStringAttack << std::endl;
				string territoryDestination;
				std::cin >> territoryDestination;
				int tIndexD = std::stoi(territoryDestination);

				Order* newNegotiate = new Negotiate(p, p->territoriesToAttack[tIndexD]);
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
    vector<Territory*> candidateTerritories = getAdjacentTerritoriesBelongingTo(p->territoriesToAttack, p->getPlayerName());

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

    // Reinforce the territories in toDefend();
    reinforceTerritories(p->territoriesToDefend);



    //// Check if 'o' is a Deploy object
    //if (Deploy *deployOrder = dynamic_cast<Deploy *>(o))
    //{
    //    // Find the strongest country
    //    Territory *strongest = getStrongestTerritory();
    //    Deploy(p, p->getReinforcmentPool(), strongest);

    //    // Replace with the content of toDefend()?
    //}

    //// Check if 'o' is a Advance object
    //if (Advance *advanceOrder = dynamic_cast<Advance *>(o))
    //{
    //    // Brainstorm about the advance recursively
    //    // for ();
    //}

    //// Check if 'o' is a Bomb object
    //if (Bomb *bombOrder = dynamic_cast<Bomb *>(o))
    //{
    //    Territory *aboutToGetBombed = getAdjacentTerritories()[0];
    //    Bomb(p, aboutToGetBombed);
    //}

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

    vector<Territory*> ownedTerritories = p->getOwnedTerritories();

    // Sort the player's territories by the number of adjacent enemy troops, then the number of their own units present on them.
    sort(ownedTerritories.begin(), ownedTerritories.end(), LessThan_AdjacentEnemyTroops_TroopsPresent());

    // Get the last NUM_TO_DEFEND territories in the sorted list.
    vector<Territory *> toDefend;

    if (ownedTerritories.size() > NUM_TO_DEFEND) // Only do this fancy copy/splicing stuff if the list of owned territories is longer than NUM_TO_DEFEND.
    {
        // The most vulnerable territories should be at the end of the list.
        toDefend.assign(ownedTerritories.end() - NUM_TO_DEFEND, ownedTerritories.end());
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
    
    // Deploy troops to own territories.
    // Move troops to weaker territories when possible?
    // Only play nonviolent cards.

    //// Check if 'o' is a Deploy object
    //if (Deploy *deployOrder = dynamic_cast<Deploy *>(o))
    //{
    //    // Find the weakest territory
    //    Territory *weakest = getWeakestTerritory();
    //    Deploy(p, p->getReinforcmentPool(), weakest);
    //}

    //// Check if 'o' is a Airlift object
    //if (Airlift *airliftOrder = dynamic_cast<Airlift *>(o))
    //{
    //    // Find the weakest territory
    //    Territory *weakest = getWeakestTerritory();
    //    //Airlift(p, p->getReinforcmentPool(), weakest); FIX THIS
    //}

    //// Check if 'o' is a Blockade object
    //if (Blockade *blockadeOrder = dynamic_cast<Blockade *>(o))
    //{
    //    Territory *aboutToGetBombed = getAdjacentTerritories()[0];
    //    Bomb(p, aboutToGetBombed);
    //}

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
    if (populateVectors == true)
    {
        p->toAttack();
        p->toDefend();
    }
    
    // Check the total number of troops that the player has across all territories. If that number diminishes, meaning the player got attacked, the neutral player becomes aggressive
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
        p->toDefend();
    }
    
    // No issueOrder method since the cheater player does not use cards!!!

    // Auto conquer the territories in toAttack?
    for (Territory* territory : p->territoriesToAttack)
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
