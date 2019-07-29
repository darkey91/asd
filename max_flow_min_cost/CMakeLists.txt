cmake_minimum_required(VERSION 3.8)
project(maxminflow)

set(CMAKE_CXX_STANDARD 14)

add_executable(maxminflow maxminflow.cpp)
add_executable(assignment assignment.cpp)
add_executable(rsp rsp.cpp)
add_executable(voyageur voyageur.cpp)
