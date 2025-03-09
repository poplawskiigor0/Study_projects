cmake_minimum_required(VERSION 3.5)

project(Project_elevator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_RELEASE")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")


add_executable(Project_elevator main.cpp elevator.h Elevator_functions.cpp Human.h Human_functions.cpp SkyScraper.h SkyScrapper_functions.cpp)

install(TARGETS Project_elevator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
