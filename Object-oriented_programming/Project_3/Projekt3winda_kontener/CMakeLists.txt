cmake_minimum_required(VERSION 3.5)

project(Projekt3winda_kontener LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_RELEASE")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

add_executable(Projekt3winda_kontener main.cpp elevator.h Human.h SkyScraper.h Room.h CleaningPlatform.h SpaceForPeople.h SmartBox.h Knot.h
    SkyScrapper.cpp Elevator.cpp Human.cpp Room.cpp CleaningPlatform.cpp SpaceForPeople.cpp SmartBox.cpp Knot.cpp)

install(TARGETS Projekt3winda_kontener
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
