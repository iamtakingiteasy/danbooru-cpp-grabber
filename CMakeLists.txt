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
  set(source-module-handler 
    ../src/Core/ModuleHandlerWin32.cpp
  )
elseif (UNIX)
  set(source-module-handler 
    ../src/Core/ModuleHandlerUnix.cpp
  )
endif (WIN32)

add_library(module-handler
  ${source-module-handler}
)

###########################################################################

project(CoreApp)

set(libs-grabber
  module-handler
)

find_package(CURL)
if (CURL_FOUND)
  set(libs-grabber ${libs-grabber}
    ${CURL_LIBRARIES}
  )
endif(CURL_FOUND)


add_executable(danbooru-cpp-grabber 
  ../src/Apps/Main.cpp
)

target_link_libraries(danbooru-cpp-grabber ${libs-grabber})
set_target_properties(danbooru-cpp-grabber PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")
