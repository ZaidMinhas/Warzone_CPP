//
// Created by minha on 11/5/2024.
//

#include "CommandProcessor.h"

#include <fstream>
#include <iostream>
#include <string>
#include "../GameEngine/GameEngine.h"

using std::cin, std::string, std::ifstream;

Command::Command(const string &command) {
    this->command = command;
}

void Command::saveEffect(const string& effect) {
    this->effect = effect;
}

string Command::getCommand() {
    return this->command;
}

string Command::getEffect() {
    return this->effect;
}

CommandProcessor::CommandProcessor(){}
CommandProcessor::CommandProcessor(CommandProcessor* commandProcessor){}

string CommandProcessor::getCommand() {
    string command = readCommand();
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


string CommandProcessor::readCommand() {
    std::string command;
    cin >> command;
    return command;
}

void CommandProcessor::saveCommand(const string& command) {
    currentCommand = new Command(command);
    commands.push_back(currentCommand);
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string& fileName):file(fileName) {
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
    }
}

string FileCommandProcessorAdapter::readCommand()  {

    string line;
    if (file >> line) {
        return line;
    } else {
        std::cerr << "End of file reached or error reading file.\n";
        return "";
    }
}


