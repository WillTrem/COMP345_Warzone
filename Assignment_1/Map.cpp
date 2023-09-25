#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Map.h"

using namespace std;

class Map
{
    vector<Territory *> mapTerritories;
    vector<string> nonExistingTerritories;
    struct Continent
    {
        string continentName;
        vector<Territory *> continentTerritories;

        Continent()
        {
            continentName = "Unknown";
            continentTerritories = vector<Territory *>();
        }

        Continent(string continentNameVal, vector<Territory *> continentTerritoriesVal)
        {
            continentName = continentNameVal;
            continentTerritories = continentTerritoriesVal;
        }
    };
    vector<Continent *> continents;

public:
    void addTerritory(Territory *territory)
    {
        mapTerritories.push_back(territory);
        // cout << territory->territoryName << " has been added to the map" << endl;
    }

    void addNeighboringTerritory(string territoryOneName, string territoryTwoName)
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

    void addContinent(string continentNameVal, vector<Territory *> continentTerritories)
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

    void printEntireMapInfo()
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

    Territory *findTerritoryByName(string territoryNameVal)
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

    bool validate(Map currentMap, Territory *startingTerritory, std::map<std::string, bool> &visitedTerritories, std::map<std::string, bool> &visitedContinents)
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
        cout << " --------------- THE CONTINENTS FORM A VALID SUBGRAPH ---------------" << endl;
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

    void deallocateMapMemory()
    {
    }

    void mapTraversal(Territory *territory, map<string, bool> &visitedTerritories, map<string, bool> &visitedContinents)
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
};

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