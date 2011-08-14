cmake_minimum_required(VERSION 2.8)

set(CMAKE_TOOLCHAIN_FILE platform.cmake)

add_definitions(-pedantic -Wall -g)

###########################################################################

include_directories(
  ../src/Headers
)

###########################################################################

project(CoreLib)

if (WIN32)
  set(source-module
    ../src/Generic/Module/Win32.cpp
  )
elseif (UNIX)
  set(source-module
    ../src/Generic/Module/Unix.cpp
  )
endif (WIN32)

add_library(module
  ${source-module}
)

###########################################################################

project(CoreApp)

set(libs-grabber
  module
)

add_executable(danbooru-cpp-grabber 
  ../src/Apps/Main.cpp
)

target_link_libraries(danbooru-cpp-grabber ${libs-grabber})
set_target_properties(danbooru-cpp-grabber PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")
