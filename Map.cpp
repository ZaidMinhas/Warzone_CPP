#include "Map.h"
using std::string;
Continent::Continent(string name, int bonus){
    this->name=name;
    this->bonus=bonus;
}
string Continent::getName(){
    return name;
}
int Continent::getBonus(){
    return bonus;
}

Territory::Territory(){}
Territory::Territory(string name, string continentName, int army, int idknmb){
    this->name=name;
    this->army=army;
    this->idknmb=idknmb;
    
    for(int i=0;i<map.continentList.size();i++){
        if (map.continentList.at(i).name==continentName){
            this->pContient=&map.continentList.at(i);
            
        }
    }
}
int Map::addContinent(string input){
    string name=input.substr(0, input.find("="));
    int bonus = std::stoi(input.substr(input.find("=")+1, input.length()));
    continentList.push_back(Continent(name, bonus));
    return 0;
}
int Map::addTerritory(string input){
    string name=input.substr(0, input.find(","));
    input=input.substr(input.find(",")+1, input.length());
    int army=std::stoi(input.substr(0, input.find(",")));
    input=input.substr(input.find(",")+1, input.length());
    int idknmb=std::stoi(input.substr(0, input.find(",")));
    input=input.substr(input.find(",")+1, input.length());
    string continent = input.substr(0, input.find(","));
    
    graph.push_back(Territory(name, continent, army, idknmb));
    
    return 0;
}
int Map::createConnections(){
    string territoryName;
    for(int i=0;i<tempInput.size();i++){
        bool loop=true;
        map.tempInput.at(i)=map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length());//removing name
        map.tempInput.at(i)=map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length());//removing first int
        map.tempInput.at(i)=map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length());//removing second int
        map.tempInput.at(i)=map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length());//removing continent
        while(loop){
            if(map.tempInput.at(i).substr(0, map.tempInput.at(i).find(","))==map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length())){
                loop=false;
            }
            territoryName=map.tempInput.at(i).substr(0, map.tempInput.at(i).find(","));
            for(int j=0;j<graph.size();j++){
                if(territoryName==graph.at(j).name){
                   graph.at(i).connections.push_back(&graph.at(j)); 
                }
            }
            map.tempInput.at(i)=map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length());
        }
    }
    return 0;
}
void Map::display(){
    std::cout<<"-------------------------------------Map-----------------------------\n";
    for(int i=0;i<map.graph.size();i++){
        std::cout<<map.graph.at(i).name<<" ("<<map.graph.at(i).pContient->name<<") -> ";
        for(int j=0;j<map.graph.at(i).connections.size();j++){
            std::cout<<map.graph.at(i).connections.at(j)->name<<" / ";
        }
        std::cout<<"\n";
    }
}




int main(){
    map.mapFile.open("Asia.map");
    string fileLine;
    std::getline(map.mapFile, fileLine);

    //-----------------------------Map Meta Data------------------------------------//
    if(fileLine.compare("[Map]\n")){
        std::getline(map.mapFile, fileLine);
        map.author=fileLine.substr(fileLine.find("=")+1, fileLine.length()-1);
        std::getline(map.mapFile, fileLine);
        map.image=fileLine.substr(fileLine.find("=")+1, fileLine.length()-1);
        std::getline(map.mapFile, fileLine);
        map.wrap=fileLine.substr(fileLine.find("=")+1, fileLine.length()-1).compare("yes");
        std::getline(map.mapFile, fileLine);
        if(fileLine.compare("scroll=none")==0){map.scroll=0;}
        else if(fileLine.compare("scroll=vertical")==0){map.scroll=1;}
        else if(fileLine.compare("scroll=horizontal")==0){map.scroll=2;}
        std::getline(map.mapFile, fileLine);
        map.warn=fileLine.substr(fileLine.find("=")+1, fileLine.length()-1).compare("yes");
    }
    while(fileLine!="[Continents]"){
        std::getline(map.mapFile, fileLine);
    };
    //-----------------------------Continent------------------------------------//
    if(fileLine.compare("[Continents]\n")){
        std::getline(map.mapFile, fileLine);
        while(fileLine!="[Territories]"&&!fileLine.empty()){
            map.addContinent(fileLine);
            std::getline(map.mapFile, fileLine);
        }
    }
    //-----------------------------Territory------------------------------------//
    while(fileLine!="[Territories]"){
        std::getline(map.mapFile, fileLine);
    };
    if(fileLine.compare("[Territories]\n")){
        while(std::getline(map.mapFile, fileLine)){
            if(!fileLine.empty()){
                map.tempInput.push_back(fileLine);
                map.addTerritory(fileLine);
            }
        }
        map.createConnections();
    }

    map.display();
    
    return 0;
}