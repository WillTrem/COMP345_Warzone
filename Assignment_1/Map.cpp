#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include "Map.h"

using namespace std;

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

// Continent assignment operator
Territory &Territory::operator=(const Territory &territory)
{
    if (&territory != this)
    {
        territoryName = territory.territoryName;
        occupierName = territory.occupierName;
        continentName = territory.continentName;
        numOfArmies = territory.numOfArmies;
        neighboringTerritories = territory.neighboringTerritories;
    }
    return *this;
}

// Continent insertion stream operator
std::ostream &operator<<(std::ostream &os, const Territory &territory)
{
    os << "Territory Name: " << territory.territoryName << std::endl;

    os << "Territory Neighbors:" << std::endl;
    for (const Territory *territory : territory.neighboringTerritories)
    {
        os << "  " << territory->territoryName << std::endl;
    }
    return os;
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

// Continent assignment operator
Continent &Continent::operator=(const Continent &continent)
{
    if (&continent != this)
    {
        continentName = continent.continentName;
        continentTerritories = continent.continentTerritories;
    }
    return *this;
}

// Continent insertion stream operator
std::ostream &operator<<(std::ostream &os, const Continent &continent)
{
    os << "Continent Name: " << continent.continentName << std::endl;

    os << "Continent Territories:" << std::endl;
    for (const Territory *territory : continent.continentTerritories)
    {
        os << "  " << territory->territoryName << std::endl;
    }
    return os;
}
// ***************************** CONTINENT *****************************

// ***************************** MAP *****************************
// Map default constructor
Map::Map()
{
    mapName = "";
    mapTerritories = vector<Territory *>();
    continents = vector<Continent *>();
    territoryWithMultipleContinents = vector<string>();
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
    territoryWithMultipleContinents = map.territoryWithMultipleContinents;
}

// Map destructor
Map::~Map()
{
    for (Continent *continent : continents)
    {
        delete continent;
    }
    continents.clear();

    for (Territory *territory : mapTerritories)
    {
        delete territory;
    }
    mapTerritories.clear();

    for (Territory *territory : continentTerritories)
    {
        delete territory;
    }
    continentTerritories.clear();
}

// Map assignment operator
Map &Map::operator=(const Map &map)
{
    if (&map != this)
    {
        mapName = map.mapName;
        continents = map.continents;
        mapTerritories = map.mapTerritories;
        territoryWithMultipleContinents = map.territoryWithMultipleContinents;
    }
    return *this;
}

// Map insertion stream operator
std::ostream &operator<<(std::ostream &os, const Map &map)
{
    cout << "Map Name: " << map.mapName << std::endl;

    cout << "Map Territories:" << std::endl;
    for (const Territory *territory : map.mapTerritories)
    {
        cout << "  " << territory << std::endl;
    }

    cout << "Continents:" << std::endl;
    for (const Continent *continent : map.continents)
    {
        cout << "  " << *continent << std::endl;
    }
    return os;
}

void Map::addTerritory(Territory *territory)
{
    mapTerritories.push_back(territory);
    cout << territory->territoryName << " has been added to the map" << endl;
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

bool Map::validate()
{
    try
    {
        std::map<std::string, bool> visitedTerritories;
        std::map<std::string, bool> visitedContinents;
        // Empty map visitedTerritories and visitedContinents to reset

        bool conditionOne = true;
        bool conditionTwo = true;
        bool conditionThree = true;

        // Traverse the map to visit every node on the map
        mapTraversal(mapTerritories[0], visitedTerritories, visitedContinents); // Pass the map by reference

        // ******************************* FIRST CHECK ******************************* //
        cout << endl;
        cout << "----------- FIRST CONDITION CHECK -----------" << endl;
        cout << endl;
        for (Territory *territory : mapTerritories)
        {
            if (visitedTerritories[territory->territoryName] == true)
            {
                cout << "Territory " << territory->territoryName << " has been traversed \n";
            }
            else
            {
                cout << "Territory " << territory->territoryName << " is not a part of the graph \n";
                conditionOne = false;
            }
        }
        cout << endl;
        cout << " --------------- THE MAP IS A VALID GRAPH --------------- " << endl;

        // ******************************* SECOND CHECK ******************************* //
        cout << endl;
        cout << "----------- SECOND CONDITION CHECK -----------" << endl;
        cout << endl;

        int numOfConnectedContinents = 0;
        for (const auto &pair : visitedContinents)
        {
            if (pair.second == true)
            {
                numOfConnectedContinents++;
            }
        }
        if (numOfConnectedContinents != continents.size())
        {
            conditionTwo = false;
        }

        if (conditionTwo == true)
        {
            cout << "--------------- THE CONTINENTS ARE VALID SUBGRAPHS ---------------" << endl;
        }
        else
        {
            cout << "--------------- THE CONTINENTS ARE INVALID SUBGRAPHS ---------------" << endl;
        }

        // ******************************* THIRD CHECK ******************************* //
        cout << endl;
        cout << "----------- THIRD CONDITION CHECK -----------" << endl;
        cout << endl;

        if (!territoryWithMultipleContinents.empty())
        {
            cout << "One of More territories has more than one continent" << endl;
            conditionThree = false;
        }
        else
        {
            cout << "Every territory belongs to only one continent" << endl;
        }

        if (conditionOne && conditionTwo && conditionThree)
        {
            cout << endl;
            cout << "THIS CONQUEST FILE IS VALID !!!" << endl;
            cout << endl;
        }
        else
        {
            cout << "THIS CONQUEST FILE IS INVALID !!!" << endl;
        }
    }
    catch (const std::exception &ex)
    {
        // Handle the exception here.
        std::cerr << "An exception occurred: " << ex.what() << std::endl;
        // Optionally, you can rethrow the exception or perform additional handling.
    }
    catch (...)
    {

        std::cerr << "An unknown exception occurred." << std::endl;
    }
}

void Map::mapTraversal(Territory *territory, map<string, bool> &visitedTerritories, map<string, bool> &visitedContinents)
{
    visitedTerritories[territory->territoryName] = true;
    visitedContinents[territory->continentName] = true;
    // cout << visitedContinents[territory->continentName] << " traversed " << endl;

    for (Territory *neighbor : territory->neighboringTerritories)
    {
        if (!visitedTerritories[neighbor->territoryName])
        {
            mapTraversal(neighbor, visitedTerritories, visitedContinents);
        }
    }
}

void Map::loadMap(string fileName)
{
    try
    {
        string myText;
        bool mapValidationPassed = false;
        // ifstream MyReadFile("Aden.map"); // To read the file for a first time
        ifstream MyReadFile(fileName); // To read the file for a first time
        // ifstream MyReadFile("Chicago.map"); // To read the file for a first time

        // We get rid of the first paragraph of the text file since it is of no use
        while (getline(MyReadFile, myText))
        {
            cout << myText << endl;
            if (myText.empty() || myText.find_first_not_of(" \t\n\v\f\r") == string::npos)
            {
                // Break from while loop when empty line is encountered
                break;
            }

            if (mapValidationPassed == false)
            {
                // Makes sure that the string does not contain ANY whitespace at the end, HOWEVER keep the whitespaces in the middle of the string
                // Find first non-whitespace character
                size_t firstNonSpace = myText.find_first_not_of(" \t\r\n");

                // Find last non-whitespace character
                size_t lastNonSpace = myText.find_last_not_of(" \t\r\n");

                // Extract the word/substring between the first non whitespace character and the last non whitespace character
                if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos)
                {
                    myText = myText.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1); // Extract the substring
                }
            }

            if (myText == "[Map]" || mapValidationPassed == true)
            {
                mapValidationPassed = true;
            }
            else
            {
                cout << endl;
                cout << "-- Invalid Map File --" << endl;
                cout << endl;
                return;
            }
        }

        // Store the continents and their respective number of territories in a map
        while (getline(MyReadFile, myText))
        {
            cout << myText << endl;
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
            cout << myText << endl;
            if (skippedLine == true)
            {
                // Split the line into an array of strings
                vector<string> words = vector<string>();
                words = split(myText, ',');
                if (!myText.empty() && !words[0].empty() && !(myText.find_first_not_of(" \t\n\v\f\r") == string::npos))
                {
                    // Converting the elements of the string array into Territory objects and storing them into an array of Territories
                    // Can't add the neighbors of the territories yet since some Territory objects havent been created
                    Territory *newTerritory = new Territory(words[0], words[1], words[2], words[3]);
                    // Empty the list of neighborTerritories for each territories
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
                    mapTerritories.push_back(newTerritory);
                    neighborTerritoryMappingList[newTerritory] = neighborTerritories;
                    neighborTerritories.clear();
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
        for (const auto &pair : mapContinents)
        {
            std::cout << "Continent: " << pair.first << ", Number of territories: " << pair.second << std::endl;
        }

        cout << endl;
        cout << "======================================================\n";
        cout << " The repository of all territories present on the map \n";
        cout << "======================================================\n";
        cout << endl;

        // Printing all territories on the map
        for (Territory *territory : mapTerritories)
        {
            cout << "Territory " << territory->territoryName << " is located at (" << territory->coordX << ", " << territory->coordY << ") and it is located on the Continent of " << territory->continentName << "\n";
        }

        // Adding all continents to the world map AND add the respective territories to each continent
        for (const auto &pair : mapContinents)
        {
            string continentName = pair.first;
            continentTerritories.clear();
            for (Territory *territory : mapTerritories)
            {
                if (continentName == territory->continentName)
                {
                    continentTerritories.push_back(territory);
                }
            }
            addContinent(continentName, continentTerritories);
            continentTerritories.clear();
        }

        // Adding the neighboring territories to the territories
        for (const auto &pair : neighborTerritoryMappingList)
        {
            Territory *currentTerritory = pair.first;
            vector<string> currentTerritoryNeighbors = pair.second;
            for (string neighbor : currentTerritoryNeighbors)
            {
                addNeighboringTerritory(currentTerritory->territoryName, neighbor);
                // cout << "Territory " << currentTerritory->territoryName << " has neighbor " << neighbor << endl;
            }
        }
    }
    catch (const std::ifstream::failure &ex)
    {
        std::cerr << "The file is cannot be loaded into a Map" << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "The file is cannot be loaded into a Map" << std::endl;
    }
    catch (...)
    {
        std::cerr << "The file is cannot be loaded into a Map" << std::endl;
    }
}
