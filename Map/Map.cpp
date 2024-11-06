#include "Map.h"
#include <string>
using namespace std;

Continent::Continent(const Continent &c){
    bonus=new int(*c.bonus);
    name=c.name;
    nbrTerritories=new int(0);
}

std::ostream & operator << (std::ostream &out, const Continent &c){
    std::cout<<"Name: "<<*c.name<<"\nBonus: "<<*c.bonus<<"\n";
    return std::cout;
}

Continent &Continent::operator = (const Continent &c){
    if(this!=&c){
        delete name;
        delete bonus;

        bonus=new int(*c.bonus);
        name=c.name;
    }

    return *this;
}

Continent::Continent(string name, int bonus){
    this->name=new string(name);
    this->bonus=new int(bonus);
    this->nbrTerritories=new int(0);
    this->index=new int(gameMap.continentList.size());
}
string Continent::getName(){
    return *name;
}
int Continent::getBonus(){
    return *bonus;
}

Territory::Territory(){}

Territory::Territory(const Territory &t){
    pContient=new Continent (*t.pContient);
    name=t.name;
    army=new int(*t.army);
    x=new int(*t.x);
    y=new int(*t.y);
    owner=new int(*t.owner);
    check=new int(*t.check);
    connections=t.connections;

}

std::ostream & operator << (std::ostream &out, const Territory &t){
    std::cout<<"Contient: \n"<<*t.pContient<<"\nName: "<<*t.name<<"\nArmy: "<<*t.army<<"\nx: "<<*t.x<<"\ny: "<<*t.y<<"\nOwner: "<<*t.owner;
    return std::cout;
}

Territory &Territory::operator=(const Territory &t){
    if(this!=&t){
        delete pContient;
        delete name;
        delete army;
        delete x;
        delete y;
        delete owner;
        delete check;
        connections.clear();

        pContient=new Continent (*t.pContient);
        name=t.name;
        army=new int(*t.army);
        x=new int(*t.x);
        y=new int(*t.y);
        owner=new int(*t.owner);
        check=new int(*t.check);
        connections=t.connections;
    }
    return *this;
}

Territory::Territory(string name, string continentName, int x, int y){
    this->name=new string(name);
    this->x=new int(x);
    this->y=new int(y);
    this->check=new int(0);
    this->army=new int(0);
    this->owner=new int(0);
    bool found=false;
    
    for(int i=0;i<gameMap.continentList.size();i++){
        if (*gameMap.continentList.at(i).name==continentName){
            this->pContient=&gameMap.continentList.at(i);
            *gameMap.continentList.at(i).nbrTerritories++;
            found=true;
        }
    }
    if(!found){
        throw InvalidMapException();
    }
}



Map::Map(){}

Map::~Map(){
    delete author;
        delete image;
        delete wrap;
        delete scroll;
        delete warn;

        graph.clear();
        tempInput.clear();
        continentList.clear();
}

void Map::clear(){
        delete gameMap.author;
        delete gameMap.image;
        delete gameMap.wrap;
        delete gameMap.scroll;
        delete gameMap.warn;

        gameMap.graph.clear();
        gameMap.tempInput.clear();
        gameMap.continentList.clear();

        gameMap.mapFile.close();
}

Map::Map(const Map &m){
    author=m.author;
    image=m.image;
    wrap=new bool(*m.wrap);
    scroll=new int(*m.scroll);
    warn=new bool(*m.warn);

    graph=m.graph;
    tempInput=m.tempInput;
    continentList=m.continentList;
}

std::ostream & operator << (std::ostream &out,Map &m){
    std::cout<<"Author: "<<*m.author<<"\nImage: "<<*m.image<<"\n Wrap: "<<*m.wrap<<"\nScroll: "<<*m.scroll<<"\nWarn: "<<*m.warn<<"\n";
    m.display();
    return std::cout;
}

Map &Map::operator=(const Map &m)
{
    if(this != &m){
        delete author;
        delete image;
        delete wrap;
        delete scroll;
        delete warn;

        graph.clear();
        tempInput.clear();
        continentList.clear();

        author=m.author;
        image=m.image;
        wrap=new bool(*m.wrap);
        scroll=new int(*m.scroll);
        warn=new bool(*m.warn);

        graph=m.graph;
        tempInput=m.tempInput;
        continentList=m.continentList;

    }
    return *this;
}

//Map map=Map(); -- same reason why map is changed
Map gameMap = Map();

/*void Map::error(){
    std::cout<<"Invalid Map\n";
    gameMap.mapFile.close();
    gameMap.clear();
    throw InvalidMapException();
}
void Map::error(string cause){
    std::cout<<"Invalid Map: "<<cause<<"\n";
    gameMap.mapFile.close();
    gameMap.clear();
    throw InvalidMapException();
}*/

int Map::addContinent(string input){
    string name=input.substr(0, input.find("="));
    int bonus = std::stoi(input.substr(input.find("=")+1, input.length()));
    continentList.push_back(Continent(name, bonus));
    return 0;
}
int Map::addTerritory(string input){
    try{
    string name=input.substr(0, input.find(","));
    input=input.substr(input.find(",")+1, input.length());
    int x=std::stoi(input.substr(0, input.find(",")));
    input=input.substr(input.find(",")+1, input.length());
    int y=std::stoi(input.substr(0, input.find(",")));
    input=input.substr(input.find(",")+1, input.length());
    string continent = input.substr(0, input.find(","));
    
    graph.push_back(Territory(name, continent, x, y));
    }catch(...){
        return 1;
    }
    
    return 0;
}

int Map::createConnections()
{
    string territoryName;
    for(int i=0;i<tempInput.size();i++){
        bool loop=true;
        bool found=false;
        gameMap.tempInput.at(i)=gameMap.tempInput.at(i).substr(gameMap.tempInput.at(i).find(",")+1, gameMap.tempInput.at(i).length());//removing name
        gameMap.tempInput.at(i)=gameMap.tempInput.at(i).substr(gameMap.tempInput.at(i).find(",")+1, gameMap.tempInput.at(i).length());//removing first int
        gameMap.tempInput.at(i)=gameMap.tempInput.at(i).substr(gameMap.tempInput.at(i).find(",")+1, gameMap.tempInput.at(i).length());//removing second int
        gameMap.tempInput.at(i)=gameMap.tempInput.at(i).substr(gameMap.tempInput.at(i).find(",")+1, gameMap.tempInput.at(i).length());//removing continent
        while(loop){
            found=false;
            if(gameMap.tempInput.at(i).substr(0, gameMap.tempInput.at(i).find(","))==gameMap.tempInput.at(i).substr(gameMap.tempInput.at(i).find(",")+1, gameMap.tempInput.at(i).length())){
                loop=false;
            }
            territoryName=gameMap.tempInput.at(i).substr(0, gameMap.tempInput.at(i).find(","));
            for(int j=0;j<graph.size();j++){
                if(territoryName==*graph.at(j).name){
                   graph.at(i).connections.push_back(&graph.at(j));
                   found=true; 
                }
            }
            if(!found){
                std::cout<<"Connection Territory not found";
                return 1;
            }
            gameMap.tempInput.at(i)=gameMap.tempInput.at(i).substr(gameMap.tempInput.at(i).find(",")+1, gameMap.tempInput.at(i).length());
        }
    }
    return 0;
}
int Map::checkConnectedGraph(Territory* pointer){
    *pointer->check=1;
    for(int i=0;i<pointer->connections.size();i++){
        if(*pointer->connections.at(i)->check==0){
            checkConnectedGraph(pointer->connections.at(i));
        }
    }
    return 0;
    
}
int Map::checkConnectedSubGraph(string name, Territory* pointer){
    
    *pointer->check=0;
    
    for(int i=0;i<pointer->connections.size();i++){
        if(*pointer->connections.at(i)->pContient->name==name&&*pointer->connections.at(i)->check==1){
            checkConnectedSubGraph(name, pointer->connections.at(i));
        }
    }
    return 0;
}





void Map::display(){
    std::cout<<"-------------------------------------Map-----------------------------\n";
    for(int i=0;i<gameMap.graph.size();i++){
        std::cout<<*gameMap.graph.at(i).name<<" ("<<*(gameMap.graph.at(i).pContient->name)<<") -> ";
        for(int j=0;j<gameMap.graph.at(i).connections.size();j++){
            std::cout<<*gameMap.graph.at(i).connections.at(j)->name<<" / ";
        }
        std::cout<<"\n";
    }
}

int Map::getUserInput(string input){
    if(input.compare(input.size()-4, 4, ".map")!=0){
        std::cout<<"File must end with .map";
        return 1;
    }else{
        
        gameMap.mapFile.open(input);
        if(gameMap.mapFile.good()){
            return 0;
        }else{
            std::cout<<"File does not exist";
            return 1;
        }
    }
}

int Map::validate(){
    //-------------------------Validating Graph----------------------------------//
    gameMap.checkConnectedGraph(&gameMap.graph.at(0));

    int j=0;
    for(int i=0;i<gameMap.graph.size();i++){
       if (*gameMap.graph.at(i).check==1){
        j++;
       };
       
    }
    
    if(j==gameMap.graph.size()){
        return 0;
    }else{
        std::cout<<"Graph is not connected";
        return 1;
    }
    

    for(int i=0;i<gameMap.continentList.size();i++){
        for(int j=0;j<gameMap.graph.size();j++){
            if(*gameMap.continentList.at(i).name==*gameMap.graph.at(j).pContient->name){
                gameMap.checkConnectedSubGraph(*gameMap.continentList.at(i).name, &gameMap.graph.at(j));
                break;
            }
        }
    }

    j=0;
    for(int i=0;i<gameMap.graph.size();i++){
       if (*gameMap.graph.at(i).check==0){
        j++;
       };
       
    }
    
    if(j==gameMap.graph.size()){
        return 0;
    }else{
        std::cout<<"Continents are not connected";
        return 1;
    }
}


int Map::loadMap(string fileName){
    try{
    if(gameMap.getUserInput(fileName)==1){
        gameMap.clear();
        gameMap.mapFile.close();
        return 1;
    };
    string fileLine;
    std::getline(gameMap.mapFile, fileLine);

    //-----------------------------Map Meta Data------------------------------------//
    if(fileLine.compare("[Map]\n")){
        std::getline(gameMap.mapFile, fileLine);
        if(fileLine.rfind("author", 0)!=0){
            std::cout<<"Invalid Meta Data 1\n";
            std::cout<<fileLine<<"\n";
            gameMap.clear();
            gameMap.mapFile.close();
            return 1;
        }
        gameMap.author=new string(fileLine.substr(fileLine.find("=")+1, fileLine.length()-1));
        std::getline(gameMap.mapFile, fileLine);
        if(fileLine.rfind("image", 0)!=0){
            std::cout<<"Invalid Meta Data 2";
            gameMap.clear();
            gameMap.mapFile.close();
            return 1;
        }
        gameMap.image=new string(fileLine.substr(fileLine.find("=")+1, fileLine.length()-1));
        std::getline(gameMap.mapFile, fileLine);
        if(fileLine.rfind("wrap", 0)!=0){
            std::cout<<"Invalid Meta Data 3";
            gameMap.clear();
            gameMap.mapFile.close();
            return 1;
        }
        gameMap.wrap=new bool(fileLine.substr(fileLine.find("=")+1, fileLine.length()-1).compare("yes"));
        std::getline(gameMap.mapFile, fileLine);
        if(fileLine.rfind("scroll", 0)!=0){
            std::cout<<"Invalid Meta Data 4";
            gameMap.clear();
            gameMap.mapFile.close();
            return 1;
        }
        if(fileLine.compare("scroll=none")==0){gameMap.scroll=new int(0);}
        else if(fileLine.compare("scroll=vertical")==0){gameMap.scroll=new int(1);}
        else if(fileLine.compare("scroll=horizontal")==0){gameMap.scroll=new int(2);}
        std::getline(gameMap.mapFile, fileLine);
        if(fileLine.rfind("warn", 0)!=0){
            std::cout<<"Invalid Meta Data 5";
            gameMap.clear();
            gameMap.mapFile.close();
            return 1;
        }
        gameMap.warn=new bool(fileLine.substr(fileLine.find("=")+1, fileLine.length()-1).compare("yes"));
    }else{
        std::cout<<"Missing [Map] tag";
            gameMap.clear();
            gameMap.mapFile.close();
            return 1;
    }
    while(fileLine!="[Continents]"){
        std::getline(gameMap.mapFile, fileLine);
        if(gameMap.mapFile.eof()){
            std::cout<<"Missing [Continents] tag";
            gameMap.clear();
            gameMap.mapFile.close();
            return 1;
        }
    };
    //-----------------------------Continent------------------------------------//
    if(fileLine.compare("[Continents]\n")){
        std::getline(gameMap.mapFile, fileLine);
        while(fileLine!="[Territories]"&&!fileLine.empty()){
            if(gameMap.addContinent(fileLine)==1){
                std::cout<<"Can't add Continent";
                gameMap.clear();
                gameMap.mapFile.close();
                return 1;
            };
            std::getline(gameMap.mapFile, fileLine);
        }
    }
    //-----------------------------Territory------------------------------------//
    while(fileLine!="[Territories]"){
        std::getline(gameMap.mapFile, fileLine);
        if(gameMap.mapFile.eof()){
            std::cout<<"Missing [Territory] tag";
            gameMap.clear();
            gameMap.mapFile.close();
            return 1;
        }
    };
    if(fileLine.compare("[Territories]\n")){
        while(std::getline(gameMap.mapFile, fileLine)){
            if(!fileLine.empty()){
                gameMap.tempInput.push_back(fileLine);
                if(gameMap.addTerritory(fileLine)==1){
                    std::cout<<"Can't add Territory";
                    gameMap.clear();
                    gameMap.mapFile.close();
                    return 1;
                };
            }
        }
        gameMap.createConnections();
    }
        gameMap.display();
    }catch(...){
            std::cout<<"Invalid map";
            gameMap.clear();
            gameMap.mapFile.close();
            return 1;
    }
    mapFile.close();
    return 0;
}

/*char * InvalidMapException::what(){
    char * msg="Invalid Map";
    return msg;
}*/