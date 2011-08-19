###########################################################################

cmake_minimum_required(VERSION 2.8)

add_definitions(-pedantic -Wall -g)

if(WIN32)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} 
    "-static-libgcc -static-libstdc++")
set(CMAKE_MODULE_LINKER_FLAGS ${CMAKE_MODULE_LINKER_FLAGS} 
    "-static-libgcc -static-libstdc++")
endif(WIN32)

###########################################################################

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests/tests.cmake)

###########################################################################

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests/include
)

###########################################################################

set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Core)
set(MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules)

include(${CORE_DIR}/Makefile.cmake)
include(${MODULES_DIR}/Makefile.cmake)
