#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>
#include "Map.h"
#include "Map.cpp"

using namespace std;

class MapDriver
{
    // Initializing the entire map of the game
    Map worldMap;
    std::map<std::string, int> mapContinents;
    std::vector<string> territoryWithMultipleContinents;
    std::vector<Territory *> mapTerritories;
    std::vector<Territory *> continentTerritories;
    std::vector<string> neighborTerritories;
    std::map<Territory *, vector<string> > neighborTerritoryMappingList;

public:
    // Custom method to split a string into an array of multiple strings with the use of a delimiter
    vector<string> split(const string &s, char delimiter)
    {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);

        while (getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }

        return tokens;
    }

    void loadMap()
    {
        string myText;
        ifstream MyReadFile("Aden.map"); // To read the file for a first time

        // We get rid of the first paragraph of the text file since it is of no use
        while (getline(MyReadFile, myText))
        {
            if (myText.empty() || myText.find_first_not_of(" \t\n\v\f\r") == string::npos)
            {
                // Break from while loop when empty line is encountered
                break;
            }
        }

        // Store the continents and their respective number of territories in a map
        while (getline(MyReadFile, myText))
        {
            if (!myText.empty())
            {
                size_t equalsPos = myText.find('=');
                if (equalsPos != std::string::npos)
                {
                    std::string continent = myText.substr(0, equalsPos);
                    int numOfTerritoryOnContinent = std::stoi(myText.substr(equalsPos + 1));
                    mapContinents[continent] = numOfTerritoryOnContinent;
                }
            }
            // Break from while loop when empty line is encountered
            if (myText.empty() || myText.find_first_not_of(" \t\n\v\f\r") == string::npos)
            {
                break;
            }
        }
        // Store and create territories
        int skippedLine = false; // SkippedLine variable purpose is to skip the first line
        while (getline(MyReadFile, myText))
        {
            if (skippedLine == true)
            {
                // Split the line into an array of strings
                vector<string> words = split(myText, ',');
                if (!myText.empty() && !words[0].empty() && !(myText.find_first_not_of(" \t\n\v\f\r") == string::npos))
                {
                    // Converting the elements of the string array into Territory objects and storing them into an array of Territories
                    // Can't add the neighbors of the territories yet since some Territory objects havent been created
                    Territory *newTerritory = new Territory(words[0], words[1], words[2], words[3]);
                    // Empty the list of neighborTerritories for each territories
                    neighborTerritories = vector<string>();

                    // Store the neighboring territories in a list, then in a map
                    for (int i = 4; i < 100; i++)
                    {
                        if (words[i].empty())
                        {
                            break;
                        }
                        else
                        {
                            // ---------------------------------------------------------------------------- //
                            // Verify that a territory does not belong to two continents

                            for (const auto &pair : mapContinents)
                            {
                                if (words[i] == pair.first)
                                {
                                    territoryWithMultipleContinents.push_back(words[0]);
                                }
                            }
                            // ---------------------------------------------------------------------------- //

                            // Makes sure that the string does not contain ANY whitespace at the end, HOWEVER keep the whitespaces in the middle of the string
                            // Find first non-whitespace character
                            size_t firstNonSpace = words[i].find_first_not_of(" \t\r\n");

                            // Find last non-whitespace character
                            size_t lastNonSpace = words[i].find_last_not_of(" \t\r\n");

                            // Extract the word/substring between the first non whitespace character and the last non whitespace character
                            if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos)
                            {
                                words[i] = words[i].substr(firstNonSpace, lastNonSpace - firstNonSpace + 1); // Extract the substring
                            }
                            neighborTerritories.push_back(words[i]);
                        }
                    }
                    neighborTerritoryMappingList[newTerritory] = neighborTerritories;

                    mapTerritories.push_back(newTerritory);
                }
            }
            else
            {
                skippedLine = true;
            }
        }
        MyReadFile.close();

        // ********************************* Data manipulation ********************************* //
        cout << endl;

        // Printing all continents
        // for (const auto &pair : mapContinents)
        // {
        //     std::cout << "Continent: " << pair.first << ", Number of territories: " << pair.second << std::endl;
        // }

        cout << endl;
        cout << "======================================================\n";
        cout << " The repository of all territories present on the map \n";
        cout << "======================================================\n";
        cout << endl;

        // Printing all territories on the map
        // for (Territory *territory : mapTerritories)
        // {
        //     cout << "Territory " << territory->territoryName << " is located at (" << territory->coordX << ", " << territory->coordY << ") and it is located on the Continent of " << territory->continentName << "\n";
        // }

        // Adding all territories to the world map
        for (Territory *territory : mapTerritories)
        {
            worldMap.addTerritory(territory);
        }

        // Adding all continents to the world map AND add the respective territories to each continent
        for (const auto &pair : mapContinents)
        {
            string continentName = pair.first;
            continentTerritories = vector<Territory *>();
            for (Territory *territory : mapTerritories)
            {
                if (continentName == territory->continentName)
                {
                    continentTerritories.push_back(territory);
                }
            }
            worldMap.addContinent(continentName, continentTerritories);
        }

        // Adding the neighboring territories to the territories
        for (const auto &pair : neighborTerritoryMappingList)
        {
            Territory *currentTerritory = pair.first;
            vector<string> currentTerritoryNeighbors = pair.second;
            for (string neighbor : currentTerritoryNeighbors)
            {
                worldMap.addNeighboringTerritory(currentTerritory->territoryName, neighbor);
                // cout << "Territory " << currentTerritory->territoryName << " has neighbor " << neighbor << endl;
            }
        }
    }

    void validateMap()
    {
        // Creation of the map data structure "visited" to store territories visited by the DFS
        std::map<std::string, bool> visitedTerritories;
        std::map<std::string, bool> visitedContinents;

        // Validate the Map
        worldMap.validate(worldMap, mapTerritories[0], visitedTerritories, visitedContinents);
    }
};

int testLoadMaps()
{
    MapDriver mapDriver;
    mapDriver.loadMap();
    mapDriver.validateMap();
    return 0;
}
