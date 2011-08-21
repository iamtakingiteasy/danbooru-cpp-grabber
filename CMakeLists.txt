###########################################################################

cmake_minimum_required(VERSION 2.8)

add_definitions(-pedantic -Wall -g)

set(CMAKE_EXE_LINKER_FLAGS "-s")
set(CMAKE_MODULE_LINKER_FLAGS "-s")

if(WIN32)
    set(CMAKE_CXX_FLAGS 
        "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_MODULE_LINKER_FLAGS 
        "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_CXX_STANDARD_LIBRARIES "")
endif(WIN32)

###########################################################################

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests/tests.cmake)

###########################################################################

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Include
    ${CMAKE_BINARY_DIR}/include
)

###########################################################################

set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Core)
set(MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules)

include(${CORE_DIR}/Makefile.cmake)
include(${MODULES_DIR}/Makefile.cmake)
