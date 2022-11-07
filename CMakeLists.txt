cmake_minimum_required(VERSION 3.23)
project(S_MDVRP)
include_directories(include)
include_directories(libs)

set(CMAKE_CXX_STANDARD 20)

add_executable(S_MDVRP main.cpp include/node.h src/node.cpp src/instance.cpp  include/route.h src/solution.cpp include/solution.h src/route.cpp include/parser.h src/parser.cpp include/gasolver.h src/gasolver.cpp)
target_compile_options(S_MDVRP PRIVATE -O3 -s -DNDEBUG -pthread)
target_link_libraries(S_MDVRP -pthread)