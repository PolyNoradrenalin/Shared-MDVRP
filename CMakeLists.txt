cmake_minimum_required(VERSION 3.23)
project(S_MDVRP)
include_directories(include)
include_directories(libs)

set(CMAKE_CXX_STANDARD 20)
find_package(Boost 1.80.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(S_MDVRP src/main.cpp include/node.h src/node.cpp src/instance.cpp include/route.h src/solution.cpp include/solution.h src/route.cpp include/parser.h src/parser.cpp include/gasolver.h src/gasolver.cpp include/utils.h src/utils.cpp)
endif()

target_link_libraries(S_MDVRP -pthread)
target_compile_options(S_MDVRP PRIVATE -O0 -s -DNDEBUG -pthread)
