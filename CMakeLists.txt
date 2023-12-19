cmake_minimum_required(VERSION 3.26)
project(projeto2)

set(CMAKE_CXX_STANDARD 17)

add_executable(projeto2 main.cpp
        src/Terminal.h
        src/Terminal.cpp
        src/Auxiliar.h
        src/Auxiliar.cpp
        src/Graph.h
        src/Airport.h
        src/Flight.h
        src/Flight.cpp
        src/Graph.cpp
        src/Airport.cpp
        src/Airline.h
        src/Airline.cpp)
