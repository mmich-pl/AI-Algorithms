cmake_minimum_required(VERSION 3.21)
project(Perceptron)

set(CMAKE_CXX_STANDARD 17)

add_executable(Perceptron src/Perceptron.cpp src/Sample.cpp src/utils.cpp src/inputParser.cpp main.cpp )
