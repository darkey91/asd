cmake_minimum_required(VERSION 3.8)
project(c)

set(CMAKE_CXX_STANDARD 14)

add_executable(snails snails.cpp)
add_executable(move_things move_things.cpp)
add_executable(space space.cpp)
add_executable(cockroach cockroach.cpp)
add_executable(tournament tournament.cpp)
add_executable(wall wall.cpp)
