cmake_minimum_required(VERSION 3.5)

project(Project_elevator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_RELEASE")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")


add_executable(Project_elevator main.cpp elevator.h Human.h SkyScraper.h Room.h CleaningPlatform.h SpaceForPeople.h SkyScrapper.cpp Elevator.cpp Human.cpp Room.cpp CleaningPlatform.cpp SpaceForPeople.cpp)

install(TARGETS Project_elevator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
