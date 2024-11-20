cmake_minimum_required(VERSION 3.10)
project(Warzone_CPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(Warzone_CPP Main.cpp
        CommandProcessor/CommandProcessingDriver.cpp
        CommandProcessor/CommandProcessor.cpp
        Orders/Orders.h
        Orders/Orders.cpp
        PlayerStrategies/PlayerStrategiesDriver.cpp
        Player/Player.cpp
        PlayerStrategies/PlayerStrategies.cpp
        GameEngine/GameEngine.cpp
        LoggingObserver/LoggingObserver.cpp
        GameEngine/TournamentDriver.cpp)