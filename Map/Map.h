#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using std::string;
using std::vector;
class Continent{
    
    public:
    string *name;
    int *bonus;
    string getName();
    int getBonus();
    Continent(string name, int bonus);
    Continent(const Continent &c);
    friend std::ostream & operator << (std::ostream &out, const Continent &c);
    Continent & operator = (const Continent &c);
};
class Territory{
    public:
    Continent *pContient;
    string *name;
    int *army;
    int *x;
    int *y;
    int *owner;
    int *check;
    vector<Territory*> connections;
    
    Territory(string name, string continentName, int x, int y);
    Territory();
    Territory(const Territory &t);
    friend std::ostream & operator << (std::ostream &out, const Territory &t);
    Territory & operator = (const Territory &t);
};

class Map{
    
    public:

    string *author;
    string *image;
    bool *wrap;
    int *scroll;
    bool *warn;

    vector<Territory> graph;
    vector<string> tempInput;
    vector<Continent> continentList;
    int addContinent(string input);
    int addTerritory(string input);
    std::ifstream mapFile;

    Map();
    ~Map();
    Map(const Map &m);
    friend std::ostream & operator << (std::ostream &out,Map &m);
    Map & operator = (const Map &m);

    int createConnections();
    int checkConnectedGraph(Territory* pointer);
    int checkConnectedSubGraph(string name, Territory* pointer);
    void display();
    void error();
    void error(string cause);
    int getUserInput();
    void loadMap();
    void validate();
    void clear();

};

extern Map map;
