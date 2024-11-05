//
// Created by minha on 11/5/2024.
//

#include "CommandProcessor.h"
#include <iostream>
#include <string>
#include "../GameEngine/GameEngine.h"

using std::cin, std::string;

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

