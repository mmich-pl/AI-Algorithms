cmake_minimum_required(VERSION 3.21)
project(kNN)

ADD_COMPILE_OPTIONS(-Wall -pedantic -pedantic-errors)
set(CMAKE_CXX_STANDARD 17)

add_executable(kNN main.cpp src/point.cpp src/kdTree.cpp src/utility.cpp src/inputParser.cpp)
