//
// Created by minha on 11/10/2024.
//

#include "CommandProcessingDriver.h"
#include "CommandProcessor.h"
#include <iostream>

using  std::string;

void testCommandProcessor(char **argv){

    if (string(argv[1]) == "-command") {
        commandProcessor = new CommandProcessor();
    }
    else if (string(argv[1]) == "-file") {
        commandProcessor = new FileCommandProcessorAdapter(argv[2]);
    }
}