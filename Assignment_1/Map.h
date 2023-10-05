#include <iostream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#ifndef MAP_H
#define MAP_H
class Territory
{
public:
    string territoryName;
    string occupierName;
    string continentName;
    string coordX;
    string coordY;
    int numOfArmies;
    std::vector<Territory *> neighboringTerritories;

    // default constructor
    Territory();

    // parameterized constructor
    Territory(string territoryNameVal, string coordXVal, string coordYVal, string continentNameVal);

    // copy constructor
    Territory(const Territory &t); // Copy Constructor

    // destructor
    ~Territory();

    // ***** Basic functions for territory attributes *****
    void setTerritoryName(string territoryNameVal);

    void setOccupierName(string occupierNameVal);

    void setTerritoryContinentName(string continentNameVal);

    void setCoordX(string coordXVal);

    void setCoordY(string coordYVal);

    void setTerritoryNumberOfArmies(int numOfArmiesVal);

    void setNeighboringTerritories(vector<Territory *> neighboringTerritoriesVal);
    // ****************************************************
};

class Continent
{
public:
    string continentName;
    vector<Territory *> continentTerritories;

    // default constructor
    Continent();

    // parameterized constructor
    Continent(string continentNameVal, vector<Territory *> continentTerritoriesVal);

    // copy constructor
    Continent(const Continent &c); // Copy Constructor

    // destructor
    ~Continent();

    // assignment operator
    friend ostream &operator<<(ostream &out, const Continent &c);
    Continent &operator=(const Continent &c);
};

class Map
{
public:
    string mapName;
    vector<Territory *> mapTerritories;
    vector<Continent *> continents;
    vector<string> nonExistingTerritories;

    // default constructor
    Map();

    // parameterized constructor
    Map(string mapName);

    // copy constructor
    Map(const Map &m);

    // destructor
    ~Map();

    void addTerritory(Territory *territory);

    void addNeighboringTerritory(string territoryOneName, string territoryTwoName);

    void addContinent(string continentNameVal, vector<Territory *> continentTerritories);

    void printEntireMapInfo();

    Territory *findTerritoryByName(string territoryNameVal);

    bool validate(Map currentMap, Territory *startingTerritory, std::map<std::string, bool> &visitedTerritories, std::map<std::string, bool> &visitedContinents);

    void mapTraversal(Territory *territory, map<string, bool> &visitedTerritories, map<string, bool> &visitedContinents);
};
#endif // end define MAP_H
