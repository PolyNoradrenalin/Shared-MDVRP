cmake_minimum_required(VERSION 3.23)
project(S_MDVRP)
include_directories(include)

set(CMAKE_CXX_STANDARD 20)

add_executable(S_MDVRP main.cpp include/node.h src/node.cpp)
