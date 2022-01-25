# header
cmake_minimum_required(VERSION 3.10)

project(test VERSION 1.0)

# settings
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_BUILD_TYPE "Debug")

# set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# includes
include_directories(${CMAKE_SOURCE_DIR}/include)

# source files
aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_FILES)

# add exe
add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/main.cpp ${SRC_FILES})

