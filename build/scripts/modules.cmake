###########################################################################

cmake_minimum_required(VERSION 2.8)

set(CMAKE_TOOLCHAIN_FILE platform.cmake)

add_definitions(-pedantic -Wall -g)

###########################################################################

include(tests/tests.cmake)

###########################################################################

include_directories(
    include
    tests/include
)

###########################################################################
