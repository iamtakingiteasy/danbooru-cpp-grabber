###########################################################################

cmake_minimum_required(VERSION 2.8)

add_definitions(-pedantic -Wall -g)

###########################################################################

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests/tests.cmake)

###########################################################################

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests/include
)

###########################################################################

set(core-sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Main.cpp
)

if (HAVE_DLOPEN)
    set(core-sources ${core-sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Modular/ModuleUnix.cpp
    )
    set(core-libs
        ${LIBS_DLOPEN}
    )
elseif(HAVE_LOADLIBRARY)
    set(core-sources ${core-sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Modular/ModuleWin.cpp
    )
else()
    message(SEND_ERROR
        "No dlopen()-like functionality found in your system. Aborting."
    )
endif (HAVE_DLOPEN)

set(core-sources ${core-sources}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Modular/Generic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Modular/Downloader.cpp
)

add_executable(danbooru-cpp-grabber ${core-sources})
target_link_libraries(danbooru-cpp-grabber ${core-libs})
