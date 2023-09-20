# CMakeList.txt : CMake project for Assignment_1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project ("Assignment_1")

# Add source to this project's executable.
add_executable (Assignment_1 
    "Assignment_1.cpp" 
    "Assignment_1.h" 
    "Cards.h" 
    "Temp.h" 
    "Cards.cpp" 
    "CardsDriver.h" 
    "CardsDriver.cpp" 
    "Player.h" 
    "Player.cpp" 
    # "Orders.h" 
    # "Orders.cpp" 
    # "OrdersDriver.h" 
    # "OrdersDriver.cpp"
    "GameEngine.h"
    "GameEngine.cpp"
    "GameEngineDriver.cpp"
    "GameEngineDriver.h"
    )

# TODO: Add tests and install targets if needed.
