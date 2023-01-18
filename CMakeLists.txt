cmake_minimum_required(VERSION 3.8)

set (This API)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set (Headers
    WinClasses.hpp
    WinProcesses.hpp
    SupportiveFunctions.hpp
    SuppClasses.hpp
    SwitchClasses.hpp
)

set (Sources
    WinClasses.cpp
    WinProcesses.cpp
    SupportiveFunctions.cpp
    SuppClasses.cpp
    SwitchClasses.cpp
)

add_executable(GAME WIN32 Life.cpp ${Headers} ${Sources})

add_library(${This} STATIC Life.cpp ${Headers} ${Sources})

add_subdirectory(Tests)