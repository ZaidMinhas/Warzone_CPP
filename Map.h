#include <iostream>
#include <vector>
#include <fstream>
using std::string;
using std::vector;
class Continent{
    
    public:
    string name;
    int bonus;
    string getName();
    int getBonus();
    Continent(string name, int bonus);
};
class Territory{
    public:
    Continent *pContient;
    string name;
    int army;
    int idknmb;
    int owner;
    vector<Territory*> connections;
    
    Territory(string name, string continentName, int army, int idknbm);
    Territory();
};

class Map{
    
    public:

    string author;
    string image;
    bool wrap;
    int scroll;
    bool warn;

    vector<Territory> graph;
    vector<string> tempInput;
    vector<Continent> continentList;
    int addContinent(string input);
    int addTerritory(string input);
    std::ifstream mapFile;

    int createConnections();
    void display();

};
Map map;