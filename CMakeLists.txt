cmake_minimum_required(VERSION 3.10)

project(codegenor VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_BUILD_TYPE "Release")

add_executable(structgenor ${CMAKE_SOURCE_DIR}/src/structgenor.cpp)

add_executable(enumgenor ${CMAKE_SOURCE_DIR}/src/enumgenor.cpp)
