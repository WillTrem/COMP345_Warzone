# CMakeList.txt : CMake project for Assignment_1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project ("Assignment_1")

# Add source to this project's executable.
add_executable (Assignment_1 
    "MainDriver.cpp" 
    "MainDriver.h" 
    "Cards.h" 
    "Cards.cpp" 
    "CardsDriver.h" 
    "CardsDriver.cpp"
    "CommandProcessing.h"
    "CommandProcessing.cpp"
    "CommandProcessingDriver.h"
    "CommandProcessingDriver.cpp"
    "Map.h"
    "Map.cpp"
    "MapDriver.h"
    "MapDriver.cpp"
    "Player.h" 
    "Player.cpp"
    "PlayerDriver.h" 
    "PlayerDriver.cpp" 
    "PlayerStrategy.h"
    "PlayerStrategy.cpp"
    "Orders.h" 
    "Orders.cpp" 
    "OrdersDriver.h" 
    "OrdersDriver.cpp"
    "GameEngine.h"
    "GameEngine.cpp"
    "GameEngineDriver.cpp"
    "GameEngineDriver.h"
    "LogObserver.h"
    "LogObserver.cpp"
    "LoggingObserverDriver.h"
    "LoggingObserverDriver.cpp"
    "GameLog.txt"
    "PlayerStrategy.h"
    "PlayerStrategy.cpp"
    "PlayerStrategyDriver.h"
    "PlayerStrategyDriver.cpp"
    "Tournament.h"
    "Tournament.cpp"
    )

# TODO: Add tests and install targets if needed.
