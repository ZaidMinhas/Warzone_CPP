#include "Map.h"
using std::string;

Continent::Continent(const Continent &c){
    bonus=new int(*c.bonus);
    name=c.name;
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
    
    for(int i=0;i<map.continentList.size();i++){
        if (*map.continentList.at(i).name==continentName){
            this->pContient=&map.continentList.at(i);
            found=true;
        }
    }
    if(!found){
        std::cout<<"Territory";
        map.error();
    }
}



Map::Map(){}

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

Map map=Map();

void Map::error(){
    std::cout<<"Invalid Map\n";
    loadMap();
}

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
        map.error();
    }
    
    return 0;
}

int Map::createConnections()
{
    string territoryName;
    for(int i=0;i<tempInput.size();i++){
        bool loop=true;
        bool found=false;
        map.tempInput.at(i)=map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length());//removing name
        map.tempInput.at(i)=map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length());//removing first int
        map.tempInput.at(i)=map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length());//removing second int
        map.tempInput.at(i)=map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length());//removing continent
        while(loop){
            found=false;
            if(map.tempInput.at(i).substr(0, map.tempInput.at(i).find(","))==map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length())){
                loop=false;
            }
            territoryName=map.tempInput.at(i).substr(0, map.tempInput.at(i).find(","));
            for(int j=0;j<graph.size();j++){
                if(territoryName==*graph.at(j).name){
                   graph.at(i).connections.push_back(&graph.at(j));
                   found=true; 
                }
            }
            if(!found){map.error();}
            map.tempInput.at(i)=map.tempInput.at(i).substr(map.tempInput.at(i).find(",")+1, map.tempInput.at(i).length());
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
    for(int i=0;i<map.graph.size();i++){
        std::cout<<*map.graph.at(i).name<<" ("<<*(map.graph.at(i).pContient->name)<<") -> ";
        for(int j=0;j<map.graph.at(i).connections.size();j++){
            std::cout<<*map.graph.at(i).connections.at(j)->name<<" / ";
        }
        std::cout<<"\n";
    }
}

void Map::getUserInput(){
    string input;
    std::cout<<"Enter the file path to your .map file: ";
    std::cin>>input;
    if(input.compare(input.size()-4, 4, ".map")!=0){
        map.error();
    }else{
        map.mapFile.open(input);
    }
}


void Map::loadMap(){
    try{
    map.getUserInput();
    string fileLine;
    std::getline(map.mapFile, fileLine);

    //-----------------------------Map Meta Data------------------------------------//
    if(fileLine.compare("[Map]\n")){
        std::getline(map.mapFile, fileLine);
        if(fileLine.rfind("author", 0)!=0){
            map.error();
        }
        map.author=new string(fileLine.substr(fileLine.find("=")+1, fileLine.length()-1));
        std::getline(map.mapFile, fileLine);
        if(fileLine.rfind("image", 0)!=0){
            map.error();
        }
        map.image=new string(fileLine.substr(fileLine.find("=")+1, fileLine.length()-1));
        std::getline(map.mapFile, fileLine);
        if(fileLine.rfind("wrap", 0)!=0){
            map.error();
        }
        map.wrap=new bool(fileLine.substr(fileLine.find("=")+1, fileLine.length()-1).compare("yes"));
        std::getline(map.mapFile, fileLine);
        if(fileLine.rfind("scroll", 0)!=0){
            map.error();
        }
        if(fileLine.compare("scroll=none")==0){map.scroll=new int(0);}
        else if(fileLine.compare("scroll=vertical")==0){map.scroll=new int(1);}
        else if(fileLine.compare("scroll=horizontal")==0){map.scroll=new int(2);}
        std::getline(map.mapFile, fileLine);
        if(fileLine.rfind("warn", 0)!=0){
            map.error();
        }
        map.warn=new bool(fileLine.substr(fileLine.find("=")+1, fileLine.length()-1).compare("yes"));
    }else{
        map.error();
    }
    while(fileLine!="[Continents]"){
        std::getline(map.mapFile, fileLine);
        if(map.mapFile.eof()){
            map.error();
        }
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
        if(map.mapFile.eof()){
            map.error();
        }
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

    //-------------------------Validating Graph----------------------------------//
    map.checkConnectedGraph(&map.graph.at(0));

    int j=0;
    for(int i=0;i<map.graph.size();i++){
       if (*map.graph.at(i).check==1){
        j++;
       };
       //std::cout<<*map.graph.at(i).name<<"  "<<*map.graph.at(i).check<<"\n";
       
    }
    
    if(j==map.graph.size()){
        //std::cout<<"Graph is connected\n";
    }else{
        map.error();
    }
    

    for(int i=0;i<map.continentList.size();i++){
        for(int j=0;j<map.graph.size();j++){
            if(*map.continentList.at(i).name==*map.graph.at(j).pContient->name){
                map.checkConnectedSubGraph(*map.continentList.at(i).name, &map.graph.at(j));
                break;
            }
        }
    }

    j=0;
    for(int i=0;i<map.graph.size();i++){
       if (*map.graph.at(i).check==0){
        j++;
       };
       //std::cout<<*map.graph.at(i).name<<"  "<<*map.graph.at(i).check<<"\n";
       
    }
    
    if(j==map.graph.size()){
        //std::cout<<"SubGraph is connected\n";
    }else{
        map.error();
    }

        map.display();
    }catch(...){
        map.error();
    }

}