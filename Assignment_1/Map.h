#include <iostream>

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

    Territory(string territoryNameVal, string coordXVal, string coordYVal, string continentNameVal) : territoryName(territoryNameVal), coordX(coordXVal), coordY(coordYVal), continentName(continentNameVal)
    {
        occupierName = "";
        numOfArmies = 0;
        neighboringTerritories = vector<Territory *>();
    }
    // Territory(string territoryNameVal, int coordXVal, int coordYVal, string continentNameVal, string occupierNameVal, int numOfArmies) : territoryName(territoryNameVal), coordX(coordXVal), coordY(coordYVal), continentName(continentNameVal), occupierName(occupierNameVal), numOfArmies(numOfArmies) {}

    // default constructor
    Territory()
    {
        territoryName = "Unknown";
        occupierName = "Unknown";
        continentName = "Unknown";
        coordX = "Unknown";
        coordY = "Unknown";
        numOfArmies = 0;
    }

    // parameterized constructor
    // Territory(string territoryNameVal, string occupierNameVal, int numOfArmiesVal)
    // {
    //     territoryName = territoryNameVal;
    //     occupierName = occupierNameVal;
    //     numOfArmies = numOfArmiesVal;
    // }

    // destructor
    // ~Territory()
    // {
    //     cout << "Destructor invoked"
    //          << "\n";
    // }

    // Basic functions for territory attributes
    void setTerritoryName(string territoryNameVal)
    {
        territoryName = territoryNameVal;
    }

    void setOccupierName(string occupierNameVal)
    {
        occupierName = occupierNameVal;
    }

    void setTerritoryContinentName(string continentNameVal)
    {
        continentName = continentNameVal;
    }

    void setCoordX(string coordXVal)
    {
        coordX = coordXVal;
    }

    void setCoordY(string coordYVal)
    {
        coordY = coordYVal;
    }

    void setTerritoryNumberOfArmies(int numOfArmiesVal)
    {
        numOfArmies = numOfArmiesVal;
    }

    void setNeighboringTerritories(vector<Territory *> neighboringTerritoriesVal)
    {
        neighboringTerritories = neighboringTerritoriesVal;
    }
};
#endif // end define MAP_H
