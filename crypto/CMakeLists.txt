cmake_minimum_required(VERSION 3.8)
project(crypto)

set(CMAKE_CXX_STANDARD 14)

add_executable(simplicity simplicity.cpp)
add_executable(prime2 prime2.cpp)
add_executable(fft fft.cpp)
