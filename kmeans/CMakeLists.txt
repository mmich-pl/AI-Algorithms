cmake_minimum_required(VERSION 3.21)
project(kmeans)

set(CMAKE_CXX_STANDARD 17)

add_executable(kmeans main.cpp src/kmeans.cpp src/point.cpp src/utility.cpp include/utility.h)
