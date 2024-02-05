cmake_minimum_required(VERSION 3.27)
project(HW1)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW1 main.cpp
        Utilities.h
        #world.h
        SARS_CoV_2.cpp
        SARS_CoV_2.h
        XBB.cpp
        XBB.h
        RCPtr.h
        BQ.cpp
        BQ.h
        CH.cpp
        CH.h
        simulation.cpp
        simulation.h
        Utilities.cpp
)
target_compile_options(
        HW1 PRIVATE
        -Wextra
        -Wall
)
