cmake_minimum_required(VERSION 3.10)

project(codegenor VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_BUILD_TYPE "Release")

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_INSTALL_PREFIX /usr/local)

install(PROGRAMS ${CMAKE_SOURCE_DIR}/bin/mystructGenor DESTINATION bin/)

install(PROGRAMS ${CMAKE_SOURCE_DIR}/bin/myenumGenor DESTINATION bin/)

install(PROGRAMS ${CMAKE_SOURCE_DIR}/bin/mycppprojGenor DESTINATION bin/)
