cmake_minimum_required(VERSION 3.10)
project(Warzone_CPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(Warzone_CPP Main.cpp
        CommandProcessor/CommandProcessingDriver.cpp
        CommandProcessor/CommandProcessor.cpp)