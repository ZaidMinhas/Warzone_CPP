cmake_minimum_required(VERSION 3.10)
project(Warzone_CPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(Warzone_CPP Main.cpp
        CommandProcessor/CommandProcessor.h
        GameEngine/GameEngine.h
        GameEngine/GameEngine.cpp
        CommandProcessor/CommandProcessor.cpp
        GameEngine/GameEngineDriver.cpp
)