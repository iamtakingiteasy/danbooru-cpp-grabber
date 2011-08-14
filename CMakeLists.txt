cmake_minimum_required(VERSION 2.8)

set(CMAKE_TOOLCHAIN_FILE platform.cmake)

add_definitions(-pedantic -Wall -g)

###########################################################################

include_directories(
  ../src/Headers
)

###########################################################################
project(DanbooruGrabberCore)

if (WIN32)
  set(sources-module
    ../src/Core/Modules/ModuleWin.cpp
  )
elseif (UNIX)
  set(sources-module
    ../src/Core/Modules/ModuleUnix.cpp
  )
  set(libs-core
    dl
  )
endif (WIN32)

add_library(module-module
  ${sources-module}
)

###########################################################################
project(DanbooruGrabberApp)

set(libs-grabber
  module-module
  ${libs-core}
)

add_executable(danbooru-cpp-grabber
  ../src/Core/Main.cpp
)

target_link_libraries(danbooru-cpp-grabber ${libs-grabber})
set_target_properties(danbooru-cpp-grabber PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")
