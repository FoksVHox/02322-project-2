cmake_minimum_required(VERSION 3.30)
project(02322_project_2 C)

set(CMAKE_C_STANDARD 11)


set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "C:/Users/Signe/Downloads/SDL2-devel-2.32.4-mingw/SDL2-2.32.4/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(02322_project_2
        main.c
        deck.c
        stack.c
        card.c
        game.c
        view.cpp
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})