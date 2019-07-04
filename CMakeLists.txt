cmake_minimum_required(VERSION 3.0)
project(ImageBatch VERSION 1.0)

# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++11)

add_executable(ImageBatch main.cpp utils.cpp argumentParser.cpp)