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
public:
    void testLoadMap()
    {
        std::vector<std::string> mapFiles;
        mapFiles.push_back("Aden.map");
        mapFiles.push_back("AdenShort.map");
        mapFiles.push_back("Alabama.map");
        mapFiles.push_back("3D Cliff.map");
        mapFiles.push_back("Lorem.txt");

        for (const string &mapFile : mapFiles)
        {
            Map *newMap = new Map(mapFile);
            newMap->loadMap(mapFile);
            try
            {
                // to make sure that newMap has territories
                if (newMap->mapTerritories.empty())
                {
                }
                else
                {
                    newMap->validate();
                    delete newMap;
                }
            }
            catch (...)
            {
                // Handle any other unknown exception.
                std::cerr << "File/Map is Invalid" << std::endl;
            }
            cout << endl
                 << endl
                 << endl;
        }

        std::cout << std::endl;
    }
};

