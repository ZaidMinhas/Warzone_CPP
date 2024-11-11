//
// Created by minha on 11/10/2024.
//

#include "CommandProcessingDriver.h"
#include "CommandProcessor.h"
#include <iostream>

using  std::string;

void testCommandProcessor(char **argv, int argc){

    if (argc==1||string(argv[1]) == "-command") {
        commandProcessor = new CommandProcessor();
    }
    else if (argc>1&&string(argv[1]) == "-file") {
        commandProcessor = new FileCommandProcessorAdapter(argv[2]);
    }
}