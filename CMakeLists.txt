cmake_minimum_required(VERSION 3.10)
project(compi3)

set(CMAKE_CXX_STANDARD 11)

add_executable(compi3 Tokens.cpp Enums.h Semantics.cpp DataStructures.cpp)