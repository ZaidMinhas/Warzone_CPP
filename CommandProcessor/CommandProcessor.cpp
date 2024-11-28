//
// Created by minha on 11/5/2024.
//

#include "CommandProcessor.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <regex>

#include "../GameEngine/GameEngine.h"

using std::cin, std::string, std::ifstream;


Command::Command(const string &command) {
    addObserver(loggingObserver);
    this->command = command;
}

Command::Command(Command& command) {
    addObserver(loggingObserver);
    this->command = command.command;

}




void Command::saveEffect(const string& effect) {
    this->effect = effect;
    Notify(*this);
}



string Command::stringToLog() {
    return "Command's Effect: " + this->effect;
}

string Command::getCommand() {
    return this->command;
}

string Command::getEffect() {
    return this->effect;
}

CommandProcessor::CommandProcessor() {
    addObserver(loggingObserver);

}
CommandProcessor::CommandProcessor(CommandProcessor* commandProcessor) {
    this->commands = vector<Command*>(commandProcessor->commands);
    addObserver(loggingObserver);
}


vector<string> CommandProcessor::splitCommand(const string command){
    std::stringstream ss(command);
    vector<string> args;
    string word;
    while(std::getline(ss, word, ' ')){
        if(!word.empty()){
            args.push_back(word);
        }
    }
    return args;
}

string CommandProcessor::getCommand() {
    std::cerr<<"Command: ";
    string command = readCommand();
    std::cerr<<"\n";
    saveCommand(command);
    return command;

}

void CommandProcessor::validate(const void *ptr) {
    if (ptr != nullptr) {
        currentCommand->saveEffect("Entering " + currentCommand->getCommand() + " State");
    }
    else {
        currentCommand->saveEffect("Incorrect command");
    }
}

bool CommandProcessor::validate(const string command){
    if (command.empty()) {
        return false;
    }
    vector<string> args = splitCommand(command);

    if (args.at(0)=="tournament" && gameEngine.getCurrentState()=="Start"){
        //Regex to see if tournament command is correct
        std::regex tournamentRegex(R"(tournament -M ([\w\\/]+\.map\s?){1,5}-P (Aggressive\s?|Benevolent\s?|Neutral\s?|Cheater\s?|Human\s?){2,4}-G ([1-5]) -D ([1-4][0-9]|50))");

        if (std::smatch match; std::regex_match(command,match, tournamentRegex)) {
            currentCommand->saveEffect("Starting a tournament");
            return true;
        }
        return false;
    }
    else if(args.at(0)=="loadmap"&&(gameEngine.getCurrentState()=="Start"||gameEngine.getCurrentState()=="Map Loaded")&&args.size()>=2){
        currentCommand->saveEffect("Loading Map");
        return true;
    }else if(args.at(0)=="validatemap"&&gameEngine.getCurrentState()=="Map Loaded"){
        currentCommand->saveEffect("Validating Map");
        return true;
    }else if(args.at(0)=="addplayer"&&(gameEngine.getCurrentState()=="Map Validated"||gameEngine.getCurrentState()=="Players Added")&&args.size()>=2){
        string strategy = (args.size() == 3) ? args.at(2) : "Human";
        currentCommand->saveEffect("Adding Player "+args.at(1) + ", using " + strategy + " Strategy");
        return true;
    }else if(args.at(0)=="gamestart"&&gameEngine.getCurrentState()=="Players Added"){
        currentCommand->saveEffect("Starting Game");
        return true;
    }else if(args.at(0)=="replay"&&gameEngine.getCurrentState()=="Win"){
        currentCommand->saveEffect("Replaying Game");
        return true;
    }else if(args.at(0)=="quit"&&gameEngine.getCurrentState()=="Win"){
        currentCommand->saveEffect("Quitting Game");
        return true;
    }else{
        currentCommand->saveEffect("Cannot use command \""+args.at(0)+"\" in state \""+gameEngine.getCurrentState()+"\"");
        return false;
    }
}


string CommandProcessor::readCommand() {
    std::string command;
    std::getline(cin, command);
    return command;
}

void CommandProcessor::saveCommand(const string& command) {
    currentCommand = new Command(command);
    commands.push_back(currentCommand);
    Notify(*this);
}

string CommandProcessor::stringToLog() {
    return "Command: " + currentCommand->getCommand();
}


FileCommandProcessorAdapter::FileCommandProcessorAdapter() = default;

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string& fileName):file(fileName) {

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
    }
}

string FileCommandProcessorAdapter::readCommand() {

    string line;
    if (getline(file, line)) {
        std::cout << line;
        return line;
    } else {
        return "";
    }
}

CommandProcessor* commandProcessor = nullptr;