# header
cmake_minimum_required(VERSION 3.10)

project(codegenor VERSION 1.0)

# settings
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_BUILD_TYPE "Debug")

# set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# includes
# include_directories(${CMAKE_SOURCE_DIR}/include)

# include_directories(${CMAKE_SOURCE_DIR}/thirdparty/include)

# add exe
add_executable(mystructGenor ${CMAKE_SOURCE_DIR}/src/structgenor.cpp)

add_executable(myenumGenor ${CMAKE_SOURCE_DIR}/src/enumgenor.cpp)

add_executable(mycppprojGenor ${CMAKE_SOURCE_DIR}/src/cppprojgenor.cpp)
