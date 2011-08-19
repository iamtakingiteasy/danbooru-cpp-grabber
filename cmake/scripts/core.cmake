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

set(core-sources
    src/Main.cpp
)

if (HAVE_DLOPEN)
    set(core-sources ${core-sources}
        src/Modular/ModuleUnix.cpp
    )
    set(core-libs
        ${LIBS_DLOPEN}
    )
elseif(HAVE_LOADLIBRARY)
    set(core-sources ${core-sources}
        src/Modular/ModuleWin.cpp
    )
else()
    message(SEND_ERROR
        "No dlopen()-like functionality found in your system. Aborting."
    )
endif (HAVE_DLOPEN)

set(core-sources ${core-sources}
    src/Modular/Generic.cpp
    src/Modular/Downloader.cpp
)

add_executable(danbooru-cpp-grabber ${core-sources})
target_link_libraries(danbooru-cpp-grabber ${core-libs})
set_target_properties(danbooru-cpp-grabber 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "output/")
