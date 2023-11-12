
#include <iostream>
#include <map>
#include <vector>

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

    // insertion stream operator
    friend ostream &operator<<(ostream &out, const Territory &t);

    // assignment operator
    Territory &operator=(const Territory &t);

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
    // TODO, initialize it
    int controlBonus;

    // default constructor
    Continent();

    // parameterized constructor
    Continent(string continentNameVal, vector<Territory *> continentTerritoriesVal);

    // copy constructor
    Continent(const Continent &c); // Copy Constructor

    // destructor
    ~Continent();

    // insertion stream operator
    friend ostream &operator<<(ostream &out, const Continent &c);

    // assignment operator
    Continent &operator=(const Continent &c);
};

class Map
{
public:
    string mapName;
    vector<Territory *> mapTerritories = vector<Territory *>();
    vector<Continent *> continents = vector<Continent *>();
    vector<string> territoryWithMultipleContinents;
    map<std::string, int> mapContinents = map<std::string, int>();
    vector<string> neighborTerritories = vector<string>();
    vector<Territory *> continentTerritories = vector<Territory *>();
    map<Territory *, vector<string>> neighborTerritoryMappingList;

    // default constructor
    Map();

    // parameterized constructor
    Map(string mapName);

    // copy constructor
    Map(const Map &m);

    // destructor
    ~Map();

    // assignment operator
    Map &operator=(const Map &map);

    // insertion stream operator
    friend std::ostream &operator<<(std::ostream &os, const Map &map);

    void addTerritory(Territory *territory);

    void addNeighboringTerritory(string territoryOneName, string territoryTwoName);

    void addContinent(string continentNameVal, vector<Territory *> continentTerritories);

    void printEntireMapInfo();

    Territory *findTerritoryByName(string territoryNameVal);

    void validate();

    void mapTraversal(Territory *territory, map<string, bool> &visitedTerritories, map<string, bool> &visitedContinents);

    void loadMap(string fileName);
};
#endif // end define MAP_H
