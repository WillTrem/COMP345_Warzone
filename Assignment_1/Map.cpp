#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Map.h"

using namespace std;
// ***************************** TERRITORY *****************************
// Territory default constructor
Territory::Territory()
{
    territoryName = "";
    occupierName = "";
    continentName = "";
    coordX = "";
    coordY = "";
    occupierName = "";
    numOfArmies = 0;
    neighboringTerritories = vector<Territory *>();
}

// Territory param constructor
Territory::Territory(string territoryNameVal, string coordXVal, string coordYVal, string continentNameVal) : territoryName(territoryNameVal), coordX(coordXVal), coordY(coordYVal), continentName(continentNameVal)
{
    occupierName = "";
    numOfArmies = 0;
    neighboringTerritories = vector<Territory *>();
}

// Territory copy constructor
Territory::Territory(const Territory &territory)
{
    territoryName = territory.territoryName;
    occupierName = territory.occupierName;
    continentName = territory.continentName;
    coordX = territory.coordX;
    coordY = territory.coordY;
    numOfArmies = territory.numOfArmies;
    neighboringTerritories = territory.neighboringTerritories;
}

// Territory destructor
Territory::~Territory()
{
    // Sets every obj inside the vector to a null pointer
    for (int i = 0; i < this->neighboringTerritories.size(); i++)
    {
        this->neighboringTerritories[i] = nullptr;
    }
    this->neighboringTerritories.clear();
}

// Set territory name
void Territory::setTerritoryName(string territoryNameVal)
{
    territoryName = territoryNameVal;
}

// Set territory occupier name
void Territory::setOccupierName(string occupierNameVal)
{
    occupierName = occupierNameVal;
}

// Set territory continent name
void Territory::setTerritoryContinentName(string continentNameVal)
{
    continentName = continentNameVal;
}

// Set the X coordinate of a territory
void Territory::setCoordX(string coordXVal)
{
    coordX = coordXVal;
}

// Set the Y coordinate of a territory
void Territory::setCoordY(string coordYVal)
{
    coordY = coordYVal;
}

// Set the number of armies of the territory
void Territory::setTerritoryNumberOfArmies(int numOfArmiesVal)
{
    numOfArmies = numOfArmiesVal;
}

// Set the neighboring territories for a territory
void Territory::setNeighboringTerritories(vector<Territory *> neighboringTerritoriesVal)
{
    neighboringTerritories = neighboringTerritoriesVal;
}

// ***************************** TERRITORY *****************************

// ***************************** CONTINENT *****************************

// Continent default constructor
Continent::Continent()
{
    continentName = "";
    continentTerritories = vector<Territory *>();
}

// Continent param constructor
Continent::Continent(string continentNameVal, vector<Territory *> continentTerritoriesVal)
{
    continentName = continentNameVal;
    continentTerritories = continentTerritoriesVal;
}

// Continent copy constructor
Continent::Continent(const Continent &continent)
{
    continentName = continent.continentName;
    continentTerritories = continent.continentTerritories;
}

// Continent destructor
Continent::~Continent()
{
    // Sets every obj inside the vector to a null pointer
    for (int i = 0; i < this->continentTerritories.size(); i++)
    {
        this->continentTerritories[i] = nullptr;
    }
    this->continentTerritories.clear();
}

// ***************************** CONTINENT *****************************

// ***************************** MAP *****************************
// Map default constructor
Map::Map()
{
    mapName = "";
    mapTerritories = vector<Territory *>();
    continents = vector<Continent *>();
    nonExistingTerritories = vector<string>();
}

// Map parameterized constructor
Map::Map(string mapNameVal)
{
    mapName = mapNameVal;
}

// Map copy constructor
Map::Map(const Map &map)
{
    mapName = map.mapName;
    mapTerritories = map.mapTerritories;
    continents = map.continents;
    nonExistingTerritories = map.nonExistingTerritories;
}

// Map destructor
Map::~Map()
{
    for (int i = 0; i < this->continents.size(); i++)
    {
        delete this->continents[i];
        this->continents[i] = nullptr;
    }
    this->continents.clear();

    for (int i = 0; i < this->mapTerritories.size(); i++)
    {
        delete this->mapTerritories[i];
        this->mapTerritories[i] = nullptr;
    }
    this->mapTerritories.clear();

    for (int i = 0; i < this->nonExistingTerritories.size(); i++)
    {
        this->nonExistingTerritories[i] = nullptr;
    }
    this->nonExistingTerritories.clear();
}

// Map assignment operator
// Map &Map::operator=(const Map &m)
// {
//     if (&m != this)
//     {
//         mapName = m.mapName;
//         continents = m.continents;
//         mapTerritories = m.mapTerritories;
//     }
//     return *this;
// }

void Map::addTerritory(Territory *territory)
{
    mapTerritories.push_back(territory);
    // cout << territory->territoryName << " has been added to the map" << endl;
}

void Map::addNeighboringTerritory(string territoryOneName, string territoryTwoName)
{
    Territory *territory1 = findTerritoryByName(territoryOneName);
    Territory *territory2 = findTerritoryByName(territoryTwoName);
    bool territoryOneFound = false;
    bool territoryTwoFound = false;

    // Loop through territories to make sure that the territories exists
    for (Territory *territory : mapTerritories)
    {
        if (territory->territoryName == territoryOneName)
        {
            territoryOneFound = true;
            // cout << territoryOneName << " exists" << endl;
            break;
        }
    }
    for (Territory *territory : mapTerritories)
    {
        if (territory->territoryName == territoryTwoName)
        {
            territoryTwoFound = true;
            // cout << territoryTwoName << " exists" << endl;
            break;
        }
    }
    // To make sure that both territories exist
    if (territoryOneFound && territoryTwoFound)
    {
        territory1->neighboringTerritories.push_back(territory2);
        // territory2->neighboringTerritories.push_back(territory1);
        // cout << "Territory " << territory1->territoryName << " now has " << territory1->neighboringTerritories.back()->territoryName << endl;
    }
    else
    {
        // cout << territoryOneName + " or " + territoryTwoName + "does not exist!" << endl;
        if (territoryOneFound)
        {
            nonExistingTerritories.push_back(territoryTwoName);
            cout << territoryTwoName + " does not exist!" << endl;
        }
        else
        {
            nonExistingTerritories.push_back(territoryOneName);
            cout << territoryOneName + " does not exist!" << endl;
        }
    }
}

void Map::addContinent(string continentNameVal, vector<Territory *> continentTerritories)
{
    for (Territory *territory : continentTerritories)
    {
        territory->setTerritoryContinentName(continentNameVal);
        // cout << territory->territoryName << " is a part of " << continentNameVal << " \n";
    }

    Continent *newContinent = new Continent(continentNameVal, continentTerritories);
    continents.push_back(newContinent);
    // cout << "The continent is " << newContinent->continentName << "\n";
}

void Map::printEntireMapInfo()
{
    for (Territory *territory : mapTerritories)
    {
        cout << territory->territoryName << " is connected to: ";
        for (Territory *neighboringTerritories : territory->neighboringTerritories)
        {
            std::cout << neighboringTerritories->territoryName << " ";
        }
        cout << "\n";
        cout << territory->territoryName << " is owned by " << territory->occupierName << " and possesses " << territory->numOfArmies << " troops \n";
        cout << std::endl;
    }

    for (Continent *continent : continents)
    {
        cout << continent->continentName << " has the following territories: ";
        for (Territory *territory : continent->continentTerritories)
        {
            cout << territory->territoryName << " ";
        }
        cout << endl;
    }
}

Territory *Map::findTerritoryByName(string territoryNameVal)
{
    for (Territory *territory : mapTerritories)
    {
        if (territory->territoryName == territoryNameVal)
        {
            return territory;
        }
    }
    return nullptr;
}

bool Map::validate(Map currentMap, Territory *startingTerritory, std::map<std::string, bool> &visitedTerritories, std::map<std::string, bool> &visitedContinents)
{
    // Empty map visitedTerritories and visitedContinents to reset
    visitedTerritories = map<string, bool>();
    visitedContinents = map<string, bool>();
    // Traverse the map to visit every node on the map
    mapTraversal(startingTerritory, visitedTerritories, visitedContinents); // Pass the map by reference

    // ******************************* FIRST CHECK ******************************* //
    cout << "First condition check" << endl;
    for (Territory *territory : mapTerritories)
    {
        if (visitedTerritories[territory->territoryName] == true)
        {
            cout << "Territory " << territory->territoryName << " has been traversed \n";
        }
        else
        {
            cout << "Territory " << territory->territoryName << " is not a part of the graph \n";
            cout << " --------------- THE MAP IS NOT A VALID GRAPH ---------------" << endl;
            return false;
        }
    }
    cout << endl;
    cout << " --------------- THE MAP IS A VALID GRAPH --------------- " << endl;
    cout << endl;

    // ******************************* SECOND CHECK ******************************* //
    for (Continent *continent : continents)
    {
        if (visitedContinents[continent->continentName] == true)
        {
            cout << "Continent " << continent->continentName << " has been traversed \n";
        }
        else
        {
            cout << " --------------- THE CONTINENTS DO NOT FORM A VALID SUBGRAPH ---------------" << endl;
            return false;
        }
    }
    cout << endl;
    cout << " --------------- THE CONTINENTS ARE VALID SUBGRAPHS ---------------" << endl;
    cout << endl;

    // ******************************* THIRD CHECK ******************************* //
    // ENSURE THAT NO TERRITORY BELONGS TO TWO CONTINENTS

    // IF A NEIGHBORING TERRITORY DOES NOT EXIST
    cout << "********** WARNING **********" << endl;
    for (string nonExistantTerritories : nonExistingTerritories)
    {
        cout << nonExistantTerritories << " does not exist!!" << endl;
    }
}

void Map::mapTraversal(Territory *territory, map<string, bool> &visitedTerritories, map<string, bool> &visitedContinents)
{
    visitedTerritories[territory->territoryName] = true;
    visitedContinents[territory->continentName] = true;

    std::cout << "Visited: " << territory->territoryName << std::endl;
    for (Territory *neighbor : territory->neighboringTerritories)
    {
        if (!visitedTerritories[neighbor->territoryName])
        {
            mapTraversal(neighbor, visitedTerritories, visitedContinents);
        }
    }
}

// ***************************** MAP *****************************

// int main()
// {
//     Map worldMap;

//     // Create territories
//     Territory *Canada = new Territory("Canada", "Brian Mulroney", 40);
//     Territory *USSR = new Territory("USSR", "Joseph Stalin", 180);
//     Territory *USA = new Territory("USA", "Abraham Lincoln", 200);
//     Territory *Cuba = new Territory("Cuba", "Fidel Castro", 10);

//     // Add territories to the map
//     worldMap.addTerritory(Canada);
//     worldMap.addTerritory(USSR);
//     worldMap.addTerritory(USA);
//     worldMap.addTerritory(Cuba);

//     // Connect the territories together with edges
//     worldMap.addNeighboringTerritory("Canada", "USSR");
//     worldMap.addNeighboringTerritory("Canada", "USA");
//     worldMap.addNeighboringTerritory("USA", "Cuba");

//     // Creating continents
//     vector<Territory *> ostanCountries;
//     ostanCountries.push_back(USSR);
//     worldMap.addContinent("Ostania", ostanCountries);

//     vector<Territory *> westaCountries;
//     westaCountries.push_back(Canada);
//     westaCountries.push_back(USA);
//     worldMap.addContinent("Westalis", westaCountries);

//     // Print the map
//     worldMap.printEntireMapInfo();

//     // Don't forget to free the allocated memory
//     delete Canada;
//     delete USSR;
//     delete USA;
//     delete Cuba;

//     return 0;
// }
