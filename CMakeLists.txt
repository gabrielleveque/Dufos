cmake_minimum_required(VERSION 3.16)
project(dufos CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(common)
add_subdirectory(engine/network)

add_executable(dufos main.cpp)

target_link_libraries(dufos PRIVATE network)
