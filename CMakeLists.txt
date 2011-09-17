###########################################################################

cmake_minimum_required(VERSION 2.8)

add_definitions(-pedantic -Wall -g)

set(CMAKE_EXE_LINKER_FLAGS "-s -g")
set(CMAKE_MODULE_LINKER_FLAGS "-s -g")

if(WIN32)
  set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static -g")
  set(CMAKE_MODULE_LINKER_FLAGS 
    "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static -g")
  set(CMAKE_CXX_STANDARD_LIBRARIES "")
endif(WIN32)

###########################################################################

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests/tests.cmake)

###########################################################################

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/include
  ${CMAKE_BINARY_DIR}/include
  )

###########################################################################

set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core)
set(MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/modules)

include(${CORE_DIR}/Makefile.cmake)
#include(${MODULES_DIR}/Makefile.cmake)
