cmake_minimum_required(VERSION 3.16)
project(dufos CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(COMMON_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../common)

set(NETWORK_LIB_NAME network)

file(GLOB_RECURSE NETWORK_SOURCES src/*.cpp)

message(STATUS "NETWORK_SOURCES: ${NETWORK_SOURCES}")

add_library(${NETWORK_LIB_NAME} SHARED ${NETWORK_SOURCES})

target_include_directories(${NETWORK_LIB_NAME} PUBLIC
    # ${CMAKE_CURRENT_SOURCE_DIR}/build/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${COMMON_DIRECTORY}/include
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/include/network
    FILES_MATCHING PATTERN "*.hpp"
)

if (APPLE)
    target_link_libraries(${NETWORK_LIB_NAME} ${COMMON_DIRECTORY}/libcommon.dylib)
elseif(UNIX)
    target_link_libraries(${NETWORK_LIB_NAME} ${COMMON_DIRECTORY}/libcommon.so)
endif()
