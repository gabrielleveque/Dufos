cmake_minimum_required(VERSION 3.16)
project(dufos CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(NETWORK_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../network)
set(COMMON_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../common)

find_package(unofficial-sodium CONFIG REQUIRED)

add_subdirectory(${NETWORK_DIRECTORY} network)

set(SERVER_EXECUTABLE dufos_server)

file(GLOB_RECURSE SERVER_SOURCES src/*.cpp)

add_executable(${SERVER_EXECUTABLE} ${SERVER_SOURCES})

target_include_directories(${SERVER_EXECUTABLE} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${NETWORK_DIRECTORY}/include>
    $<BUILD_INTERFACE:${COMMON_DIRECTORY}/include>
)

target_link_libraries(${SERVER_EXECUTABLE} PUBLIC network unofficial-sodium::sodium)
