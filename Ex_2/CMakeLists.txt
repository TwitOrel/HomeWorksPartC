cmake_minimum_required(VERSION 3.27)
project(Ex_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Ex_2 main.cpp
        Omsterdam.cpp
        Omsterdam.h
        Graph.h
        Station.cpp
        Station.h
        Intercity.cpp
        Intercity.h
        Vehicles.cpp
        Vehicles.h
        Bus.cpp
        Bus.h
        Tram.cpp
        Tram.h
        Rail.cpp
        Rail.h
        Sprinter.cpp
        Sprinter.h
        Stad.cpp
        Stad.h
        Centraal.cpp
        Centraal.h
        Utilities.cpp
        Utilities.h
)
